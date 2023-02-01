/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:22:52 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/24 14:33:59 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	lock_philo(t_philo *p)
{
	if (p->id == p->d->n_of_philo - 1 && (p->d->n_of_philo % 2 == 0))
	{
		pthread_mutex_lock(&p->d->mutex_forks[0]);
		pthread_mutex_lock(&p->d->mutex_forks[p->id]);
	}
	else if (p->id == p->d->n_of_philo - 1 && (p->d->n_of_philo % 2 != 0))
	{
		pthread_mutex_lock(&p->d->mutex_forks[0]);
		pthread_mutex_lock(&p->d->mutex_forks[p->id]);
	}
	else if (p->d->n_of_philo % 2 == 0)
	{
		pthread_mutex_lock(&p->d->mutex_forks[p->id]);
		pthread_mutex_lock(&p->d->mutex_forks[p->id + 1]);
	}
	else
	{
		pthread_mutex_lock(&p->d->mutex_forks[p->id]);
		pthread_mutex_lock(&p->d->mutex_forks[p->id + 1]);
	}
}

void	unlock_philo(t_philo *p)
{
	if (p->id == p->d->n_of_philo - 1 && (p->d->n_of_philo % 2 == 0))
	{
		pthread_mutex_unlock(&p->d->mutex_forks[0]);
		pthread_mutex_unlock(&p->d->mutex_forks[p->id]);
	}
	else if (p->id == p->d->n_of_philo - 1 && (p->d->n_of_philo % 2 != 0))
	{
		pthread_mutex_unlock(&p->d->mutex_forks[p->id]);
		pthread_mutex_unlock(&p->d->mutex_forks[0]);
	}
	else if (p->d->n_of_philo % 2 == 0)
	{
		pthread_mutex_unlock(&p->d->mutex_forks[p->id]);
		pthread_mutex_unlock(&p->d->mutex_forks[p->id + 1]);
	}
	else
	{
		pthread_mutex_unlock(&p->d->mutex_forks[p->id + 1]);
		pthread_mutex_unlock(&p->d->mutex_forks[p->id]);
	}
}

int	ft_philo_pair(t_philo *p, t_data *d)
{
	d->i = 0;
	while (d->i < d->n_of_philo)
	{
		init_philo(p, d, d->i);
		if (pthread_create(&p[d->i].thread, NULL, routine, &p[d->i]) != 0)
		{
			pthread_join(p[d->i].thread, NULL);
			ft_destroy(p, d);
			return (0);
		}
		d->i += 2;
	}
	return (1);
}

int	ft_philo_impair(t_philo *p, t_data *d)
{
	d->i = 1;
	while (d->i < d->n_of_philo)
	{
		init_philo(p, d, d->i);
		if (pthread_create(&p[d->i].thread, NULL, routine, &p[d->i]) != 0)
		{
			pthread_join(p[d->i].thread, NULL);
			ft_destroy(p, d);
			return (0);
		}
		d->i += 2;
	}
	return (1);
}

int	ft_create_thread(t_philo *philo, t_data *d)
{
	if (ft_philo_pair(philo, d) == 0)
		return (0);
	usleep(130);
	if (ft_philo_impair(philo, d) == 0)
		return (0);
	return (0);
}
