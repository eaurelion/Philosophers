/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:31:42 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:31:44 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

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
	phinfo->condition = 1;
	sem_unlink("/fork");
	sem_unlink("/print_c");
	sem_unlink("/dead");
	sem_unlink("/sem_eaten");
	phinfo->fork = sem_open("/fork", O_CREAT, 0777, phinfo->numph);
	phinfo->print_c = sem_open("/print_c", O_CREAT, 0777, 1);
	phinfo->dead = sem_open("/dead", O_CREAT, 0777, 0);
	phinfo->sem_eaten = sem_open("/sem_eaten", O_CREAT, 0777, 0);
	if (argc == 6)
		phinfo->m_eat = ft_atoi(argv[5]);
	else
		phinfo->m_eat = 0;
	return (phinfo);
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
	return (sub_main(argv, philos));
}

int	sub_main(char **argv, t_philos *ph)
{
	int			i;
	pthread_t	th;

	i = -1;
	if (argv[5])
		pthread_create(&th, NULL, &all_have_eat, ph);
	while (++i < ph->phinfo->numph)
	{
		ph[i].pid = fork();
		if (ph[i].pid == 0)
			main_function(&(ph[i]));
	}
	sem_wait(ph->phinfo->dead);
	ph->phinfo->condition = 0;
	sem_post(ph->phinfo->sem_eaten);
	i = -1;
	while (++i < ph->phinfo->numph)
		kill(ph[i].pid, SIGKILL);
	if (argv[5])
		pthread_join(th, NULL);
	free_all(ph);
	return (0);
}

void    *all_have_eat(void *philos)
{
    t_philos    *ph;
    int            full;

    ph = philos;
    full = 0;
    while (full < ph->phinfo->m_eat * ph->phinfo->numph)
    {
        sem_wait(ph->phinfo->sem_eaten);
        if (ph->phinfo->condition == 0)
            return (NULL);
        full++;
    }
    sem_post(ph->phinfo->dead);
    return (0);
}

void    free_all(t_philos *ph)
{
    sem_close(ph->phinfo->fork);
    sem_unlink("/fork");
    sem_close(ph->phinfo->print_c);
    sem_unlink("/print_c");
    sem_close(ph->phinfo->dead);
    sem_unlink("/dead");
    sem_close(ph->phinfo->sem_eaten);
    sem_unlink("/sem_eaten");
    free(ph->phinfo);
    free(ph);
}
