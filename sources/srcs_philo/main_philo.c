/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:26:21 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/25 16:16:59 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_usleep(t_philo *philo, time_t time)
{
	time_t	wake_up;

	wake_up = get_time(philo->d->start) + time;
	while (get_time(philo->d->start) < wake_up)
	{
		if (check_death(philo) == -1)
			break ;
		usleep(50);
	}
}

void	check_still_locked(int value, t_philo *p)
{
	if (value == 2)
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
}

int	main(int argc, char **argv)
{
	t_data	d;
	t_philo	*philo;

	if (argc >= 5 && argc <= 6)
	{
		if (check_argv(argc, argv, &d) == 0)
			return (0);
		philo = malloc (sizeof(t_philo) * d.n_of_philo);
		if (philo == NULL)
			return (0);
		d.start = get_time(0);
		ft_create_thread (philo, &d);
		ft_end_philo(philo, &d);
	}
	else
		write (2, "ERROR\nInvalid Argument\n", 23);
	return (0);
}
