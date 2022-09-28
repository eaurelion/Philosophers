/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:08:51 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:08:54 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	taking_fork(t_philos *ph)
{
	if (ph->philosopher_id % 2 == 0)
		usleep (50);
	pthread_mutex_lock(&ph->phinfo->fork[ph->philosopher_id - 1]);
	print_condition(ph, "has taken a fork");
	if (ph->philosopher_id == ph->phinfo->numph)
		pthread_mutex_lock(&ph->phinfo->fork[0]);
	else
		pthread_mutex_lock(&ph->phinfo->fork[ph->philosopher_id]);
	print_condition(ph, "has taken a fork");
}

void	eating(t_philos *ph)
{
	print_condition(ph, "is eating");
	ph->time_last_eat = get_time();
	ph->n_eat++;
	during(ph->phinfo->time_to_eat, ph);
	pthread_mutex_unlock(&ph->phinfo->fork[ph->philosopher_id - 1]);
	if (ph->philosopher_id == ph->phinfo->numph)
		pthread_mutex_unlock(&ph->phinfo->fork[0]);
	else
		pthread_mutex_unlock(&ph->phinfo->fork[ph->philosopher_id]);
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

	pthread_mutex_lock(&ph->phinfo->print_c);
	time = get_time() - ph->phinfo->time_last_eat;
	if (ph->phinfo->condition == 1)
		printf("%lld %d %s\n", time, ph->philosopher_id, condition);
	pthread_mutex_unlock(&ph->phinfo->print_c);
}

void    time_to_beginning(t_philos *ph)
{
    while (get_time() - ph->phinfo->time_last_eat < ph->first_start_to_eat)
        usleep(200);
}

int    condition_to_stop(t_philos *ph)
{
    if (ph->phinfo->numph % 2 == 0)
    {
        if (ph->phinfo->m_eat && ph->n_eat == ph->phinfo->m_eat
            && ph->philosopher_id % 2 == 0)
            return (1);
        else
            return (0);
    }
    else
    {
        if (ph->phinfo->m_eat && ph->n_eat == ph->phinfo->m_eat
            && (ph->philosopher_id % 2 == 0 || ph->philosopher_id
                == ph->phinfo->numph))
            return (1);
        else
            return (0);
    }
}
