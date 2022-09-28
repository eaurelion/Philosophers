/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 21:58:46 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 21:58:49 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_phinfo
{
	int				numph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				m_eat;
	int				condition;
	long long		time_last_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_c;
}				t_phinfo;

typedef struct s_philos
{
	int				philosopher_id;
	int				n_eat;
	long long		time_last_eat;
	t_phinfo		*phinfo;
	double			first_start_to_eat;
}				t_philos;

t_phinfo		*init_phinfo(int argc, char **argv);
t_philos		*init_philos(int argc, char **argv);
pthread_mutex_t	*init_fork(t_phinfo *phinfo);
int				main(int argc, char **argv);
int				philos_are_threads(t_philos *ph);
void			start_to_eating(t_philos *ph);
int				sub_main_function(t_philos *ph);

void			taking_fork(t_philos *ph);
void			eating(t_philos *ph);
void			during(long long time, t_philos *ph);
void			*is_dead(void *philos);
int				check_condition(t_philos *ph);
void			*main_function(void *philos);
void			time_to_beginning(t_philos *ph);
int				condition_to_stop(t_philos *ph);

int				ft_atoi(const char *str);
long long		get_time(void);
void			print_condition(t_philos *ph, char *condition);
void			print_dead(t_philos *ph);

#endif
