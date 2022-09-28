/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:08:43 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:08:45 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_dead(t_philos *ph)
{
	long long	time;

	pthread_mutex_lock(&ph->phinfo->print_c);
	time = get_time() - ph->phinfo->time_last_eat;
	if (ph->phinfo->condition == 1)
	{
		ph->phinfo->condition = 0;
		printf("%lld %d died\n", time, ph->philosopher_id);
	}
	pthread_mutex_unlock(&ph->phinfo->print_c);
}

int	check_condition(t_philos *ph)
{
	long long	time;

	usleep(90);
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

int	sub_main_function(t_philos *ph)
{
	taking_fork(ph);
	eating(ph);
	print_condition(ph, "is sleeping");
	if (condition_to_stop(ph))
		return (0);
	during(ph->phinfo->time_to_sleep, ph);
	print_condition(ph, "is thinking");
	if (ph->phinfo->m_eat && ph->n_eat == ph->phinfo->m_eat)
		return (0);
	return (1);
}

void	*main_function(void *philos)
{
	pthread_t	th;
	t_philos	*ph;
	int			n;

	ph = philos;
	n = 0;
	pthread_create(&th, NULL, &is_dead, ph);
	pthread_detach(th);
	while (ph->phinfo->condition == 1)
	{
		check_condition(ph);
		if (ph->n_eat == 0)
			time_to_beginning(ph);
		if (ph->phinfo->numph != 1)
		{
			n = sub_main_function(ph);
			if (!n)
				break ;
		}
		check_condition(ph);
	}
	return (0);
}
