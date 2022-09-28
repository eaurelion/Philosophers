/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:32:06 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:32:08 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	taking_fork(t_philos *ph)
{
	sem_wait(ph->phinfo->fork);
	print_condition(ph, "has taken a fork");
	sem_wait(ph->phinfo->fork);
	print_condition(ph, "has taken a fork");
}

void	eating(t_philos *ph)
{
	print_condition(ph, "is eating");
	ph->time_last_eat = get_time();
	ph->n_eat++;
	during(ph->phinfo->time_to_eat, ph);
	sem_post(ph->phinfo->fork);
	sem_post(ph->phinfo->fork);
	sem_post(ph->phinfo->sem_eaten);
}

void	during(long long time, t_philos *ph)
{
	long long	n_time;

	n_time = get_time();
	check_condition(ph);
	if (ph->phinfo->condition == 1)
	{
		usleep(time * 500);
		while (get_time() - n_time < time)
			usleep(200);
	}
	else
		print_dead(ph);
}

void	*is_dead(void *philos)
{
	t_philos	*ph;

	ph = philos;
	while (ph->phinfo->condition == 1)
	{
		check_condition(ph);
		usleep(3000);
	}
	return (philos);
}

void	print_condition(t_philos *ph, char *condition)
{
	long long	time;

	sem_wait(ph->phinfo->print_c);
	time = get_time() - ph->phinfo->time_last_eat;
	if (ph->phinfo->condition == 1)
		printf("%lld %d %s\n", time, ph->philosopher_id, condition);
	sem_post(ph->phinfo->print_c);
}
