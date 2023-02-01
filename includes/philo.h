/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:28:25 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/21 17:11:45 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	time_t			start;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	pthread_mutex_t	mutex_forks[250];
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_time;
	pthread_mutex_t	mutex_control;
	pthread_mutex_t	mutex_nb_of_philo;
	int				control;
	int				n_of_philo;
	int				x_of_eats;
	int				nb_arg;
	int				i;
	int				death;
}					t_data;

typedef struct s_philo
{
	time_t			last_time_ate;
	int				has_ate;
	int				id;
	int				i;
	pthread_t		thread;
	t_data			*d;
}					t_philo;

// Check des Arguments :
int		check_argv(int ac, char **av, t_data *d);
int		check_number_of_philosophers(t_data *d);
int		ft_init_data(int ac, char **av, t_data *d);
void	ft_init_mutex(t_data *d);
void	init_philo(t_philo *philo, t_data *data, int i);

// THREADS :
int		ft_create_thread(t_philo *philo, t_data *d);
int		ft_philo_pair(t_philo *philo, t_data *d);
int		ft_philo_impair(t_philo *philo, t_data *d);

//ROUTINE :
void	*routine(void *arg);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
void	check_thinking(t_philo *p);
void	lock_philo(t_philo *philo);
void	unlock_philo(t_philo *philo);

//	Check de mort avant chaque action :
void	ft_usleep(t_philo *philo, time_t time);
void	check_still_locked(int value, t_philo *philo);
int		check_data_death(t_philo *philo);
int		check_death(t_philo *philo);
int		check_control(t_philo *philo);

// DESTRUCTION ET FREE:
void	ft_end_philo(t_philo *philo, t_data *data);
void	ft_destroy(t_philo *philo, t_data *data);

//	UTILS :
time_t	get_time(time_t start);
int		ft_atoi(const char *nptr);
int		ft_str_is_numeric(char *str);
void	ft_printf(char *str, time_t time, int id, t_philo *philo);

#endif
