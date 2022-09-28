/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:32:13 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:32:14 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	print_dead(t_philos *ph)
{
	long long	time;

	sem_wait(ph->phinfo->print_c);
	time = get_time() - ph->phinfo->time_last_eat;
	printf("%lld %d died\n", time, ph->philosopher_id);
	sem_post(ph->phinfo->dead);
}

int	check_condition(t_philos *ph)
{
	long long	time;

	usleep(100);
	time = get_time();
	if (ph->time_last_eat == 0)
		ph->time_last_eat = get_time();
	if (ph->phinfo->condition == 0)
		return (0);
	if (time - ph->time_last_eat > ph->phinfo->time_to_die)
	{
		print_dead(ph);
		return (0);
	}
	return (1);
}

void	*main_function(void *philos)
{
	pthread_t	th;
	t_philos	*ph;

	ph = philos;
	pthread_create(&th, NULL, &is_dead, ph);
	pthread_detach(th);
	while (ph->phinfo->condition == 1)
	{
		check_condition(ph);
		if (ph->phinfo->numph != 1)
		{
			taking_fork(ph);
			eating(ph);
			print_condition(ph, "is sleeping");
			during(ph->phinfo->time_to_sleep, ph);
			print_condition(ph, "is thinking");
		}
		check_condition(ph);
	}
	exit (EXIT_SUCCESS);
}
