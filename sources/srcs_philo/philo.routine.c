/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:58:31 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/24 15:16:57 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	check_thinking(t_philo *p)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&p->d->mutex_control);
	p->d->control = 1;
	pthread_mutex_unlock(&p->d->mutex_control);
	ft_printf("%ld %d is thinking\n", get_time(p->d->start), p->id + 1, p);
	res = p->d->time_to_die - p->d->time_to_eat - p->d->time_to_sleep;
	ft_usleep(p, res);
	if (p->d->death == 0)
	{
		usleep(500);
		pthread_mutex_lock(&p->d->mutex_print);
		printf("%ld %d died\n", get_time(p->d->start), p->id + 1);
		pthread_mutex_unlock(&p->d->mutex_print);
	}
	pthread_mutex_lock(&p->d->mutex_death);
	p->d->death = 1;
	pthread_mutex_unlock(&p->d->mutex_death);
}

int	eating(t_philo *p)
{
	if (check_death(p) == -1)
		return (0);
	lock_philo(p);
	ft_printf("%ld %d has taken a fork\n", get_time(p->d->start), p->id + 1, p);
	ft_printf("%ld %d has taken a fork\n", get_time(p->d->start), p->id + 1, p);
	ft_printf("%ld %d is eating\n", get_time(p->d->start), p->id + 1, p);
	if (check_death(p) == -1)
	{
		check_still_locked(2, p);
		return (0);
	}
	p->last_time_ate = get_time(0);
	ft_usleep (p, p->d->time_to_eat);
	if (check_death(p) == -1)
	{
		check_still_locked(2, p);
		return (0);
	}
	p->has_ate++;
	unlock_philo (p);
	return (1);
}

int	sleeping(t_philo *p)
{
	if (check_death(p) == -1)
		return (0);
	ft_printf("%ld %d is sleeping\n", get_time(p->d->start), p->id + 1, p);
	ft_usleep (p, p->d->time_to_sleep);
	if (check_death(p) == -1)
		return (0);
	return (1);
}

int	thinking(t_philo *p)
{
	if (check_data_death(p) == 1)
		return (0);
	if (p->d->n_of_philo % 2 != 0
		&& p->d->time_to_eat >= p->d->time_to_sleep
		&& (p->d->time_to_eat + p->d->time_to_sleep
			>= (p->d->time_to_die + p->d->time_to_sleep) / 2))
	{
		if (check_control(p) == 0)
			return (check_thinking(p), 0);
	}
	else if (p->d->n_of_philo % 2 == 0
		&& p->d->time_to_eat >= p->d->time_to_sleep
		&& (p->d->time_to_eat > p->d->time_to_die / 2)
		&& (p->d->time_to_die - p->d->time_to_eat >= p->d->time_to_sleep))
	{
		if (check_control(p) == 0)
		{
			check_thinking(p);
			return (0);
		}
	}
	ft_printf("%ld %d is thinking\n", get_time(p->d->start), p->id + 1, p);
	usleep(100);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_data_death(philo) == 0)
	{
		if (eating(philo) == 0)
			return (NULL);
		usleep(30);
		if (sleeping(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
	}
	return (NULL);
}
