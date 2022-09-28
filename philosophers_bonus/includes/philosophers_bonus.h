/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:31:12 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:31:14 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_phinfo
{
	int			numph;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			m_eat;
	int			condition;
	long long	time_last_eat;
	sem_t		*fork;
	sem_t		*print_c;
	sem_t		*dead;
	sem_t		*sem_eaten;

}				t_phinfo;

typedef struct s_philos
{
	int			philosopher_id;
	int			n_eat;
	long long	time_last_eat;
	t_phinfo	*phinfo;
	pid_t		pid;
}				t_philos;

t_phinfo		*init_phinfo(int argc, char **argv);
t_philos		*init_philos(int argc, char **argv);
pthread_mutex_t	*init_fork(t_phinfo *phinfo);
int				main(int argc, char **argv);
int				sub_main(char **argv, t_philos *ph);
void			*all_have_eat(void *philos);
void			free_all(t_philos *ph);

void			taking_fork(t_philos *ph);
void			eating(t_philos *ph);
void			during(long long time, t_philos *ph);
void			*is_dead(void *philos);
int				check_condition(t_philos *ph);
void			*main_function(void *philos);
void			print_condition(t_philos *ph, char *condition);
void			print_dead(t_philos *ph);

int				ft_atoi(const char *str);
long long		get_time(void);

#endif
