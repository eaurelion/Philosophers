/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:59:25 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 21:59:28 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philos	*init_philos(int argc, char **argv)
{
	t_philos	*ph;
	t_phinfo	*phinfo;
	int			i;

	i = 0;
	phinfo = init_phinfo(argc, argv);
	ph = (t_philos *)malloc(sizeof(t_philos) * phinfo->numph);
	while (i < phinfo->numph)
	{
		ph[i].philosopher_id = i + 1;
		ph[i].phinfo = phinfo;
		ph[i].time_last_eat = 0;
		ph[i].n_eat = 0;
		start_to_eating(&ph[i]);
		i++;
	}
	return (ph);
}

t_phinfo	*init_phinfo(int argc, char **argv)
{
	t_phinfo	*phinfo;

	phinfo = (t_phinfo *)malloc(sizeof(t_phinfo));
	phinfo->numph = ft_atoi(argv[1]);
	phinfo->time_to_die = ft_atoi(argv[2]);
	phinfo->time_to_eat = ft_atoi(argv[3]);
	phinfo->time_to_sleep = ft_atoi(argv[4]);
	phinfo->time_last_eat = get_time();
	phinfo->fork = init_fork(phinfo);
	phinfo->condition = 1;
	pthread_mutex_init(&phinfo->print_c, NULL);
	if (argc == 6)
		phinfo->m_eat = ft_atoi(argv[5]);
	else
		phinfo->m_eat = 0;
	return (phinfo);
}

pthread_mutex_t	*init_fork(t_phinfo *phinfo)
{
	pthread_mutex_t	*fork;
	int				i;

	i = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* phinfo->numph);
	while (i < phinfo->numph)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;

	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1
		|| (argc == 6 && ft_atoi(argv[5]) < 1))
	{
		printf("Wrong argument(s)!\n");
		return (1);
	}
	philos = init_philos(argc, argv);
	return (philos_are_threads(philos));
}

int	philos_are_threads(t_philos *ph)
{
	pthread_t	*th;
	int			i;
	int			j;

	i = 0;
	j = 0;
	th = (pthread_t *)malloc(sizeof(pthread_t) * (ph->phinfo->numph));
	while (i < ph->phinfo->numph)
	{
		pthread_create(&th[i], NULL, &main_function, &ph[i]);
		i++;
	}
	while (j < ph->phinfo->numph)
	{
		pthread_join(th[j], NULL);
		j++;
	}
	free(th);
	free(ph->phinfo->fork);
	free(ph->phinfo);
	free(ph);
	return (0);
}

void    start_to_eating(t_philos *ph)
{
    if (ph->philosopher_id % 2 == 0)
        ph->first_start_to_eat = ph->phinfo->time_to_eat;
    else if (ph->philosopher_id == ph->phinfo->numph && ph->phinfo->numph
        % 2 == 1)
        ph->first_start_to_eat = 2 * ph->phinfo->time_to_eat;
    else
        ph->first_start_to_eat = 0;
}
