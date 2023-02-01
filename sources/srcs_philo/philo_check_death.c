/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_death.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:38:19 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/24 15:10:31 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_one_philo(t_philo *p)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&p->d->mutex_nb_of_philo);
	check = p->d->n_of_philo;
	pthread_mutex_unlock(&p->d->mutex_nb_of_philo);
	if (check == 1)
	{		
		pthread_mutex_lock(&p->d->mutex_death);
		p->d->death = 1;
		pthread_mutex_unlock(&p->d->mutex_death);
		pthread_mutex_lock(&p->d->mutex_print);
		printf("%ld %d has taken a fork\n", get_time(p->d->start), p->id + 1);
		usleep (p->d->time_to_die * 1000);
		printf("%ld %d died\n", get_time(p->d->start), p->id + 1);
		pthread_mutex_unlock(&p->d->mutex_print);
		return (-1);
	}
	return (0);
}

int	check_control(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&philo->d->mutex_control);
	check = philo->d->control;
	pthread_mutex_unlock(&philo->d->mutex_control);
	return (check);
}

int	check_data_death(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&philo->d->mutex_death);
	check = philo->d->death;
	pthread_mutex_unlock(&philo->d->mutex_death);
	return (check);
}

int	check_death(t_philo *p)
{
	if (check_one_philo(p) == 1)
		return (-1);
	if (check_data_death(p) == 1)
		return (-1);
	if (p->d->x_of_eats != 0
		&& (p->has_ate == p->d->x_of_eats))
		return (-1);
	else if (get_time(0) - p->last_time_ate > p->d->time_to_die)
	{
		if (check_data_death(p) == 0)
		{
			pthread_mutex_lock(&p->d->mutex_death);
			p->d->death = 1;
			pthread_mutex_unlock(&p->d->mutex_death);
			usleep(100);
			pthread_mutex_lock(&p->d->mutex_print);
			printf("%ld %d died\n", get_time(p->d->start), p->id + 1);
			pthread_mutex_unlock(&p->d->mutex_print);
		}
		return (-1);
	}
	return (0);
}
