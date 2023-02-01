/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:25:28 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/21 16:09:03 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	check_number_of_philosophers(t_data *d)
{
	if (d->n_of_philo == 0)
	{
		write (2, "ERROR\nNeed One Philo\n", 21);
		return (0);
	}
	if (d->n_of_philo > 200)
	{
		write (2, "ERROR\nToo many Philosophers\n", 28);
		return (0);
	}
	return (1);
}

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo[i].d = data;
	philo[i].id = i;
	philo[i].last_time_ate = get_time(0);
	philo[i].has_ate = 0;
}

void	ft_init_mutex(t_data *d)
{
	int	j;

	j = 0;
	while (j < d->n_of_philo)
	{
		pthread_mutex_init(&d->mutex_forks[j], NULL);
		j++;
	}
	pthread_mutex_init(&d->mutex_print, NULL);
	pthread_mutex_init(&d->mutex_control, NULL);
	pthread_mutex_init(&d->mutex_death, NULL);
	pthread_mutex_init(&d->mutex_time, NULL);
	pthread_mutex_init(&d->mutex_nb_of_philo, NULL);
}

int	ft_init_data(int ac, char **av, t_data *d)
{
	d->n_of_philo = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	if (check_number_of_philosophers(d) == 0)
		return (0);
	ft_init_mutex(d);
	d->i = 0;
	d->nb_arg = ac;
	d->death = 0;
	d->control = 0;
	d->x_of_eats = 0;
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{	
		d->x_of_eats = ft_atoi(av[5]);
		if (d->x_of_eats == 0)
		{
			write (2, "ERROR\nNeed one meal\n", 20);
			return (0);
		}
	}
	return (1);
}

int	check_argv(int ac, char **av, t_data *d)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 0)
		{
			write (2, "ERROR\nInvalid Argument\n", 23);
			return (0);
		}
		i++;
	}
	if (ft_init_data(ac, av, d) == 0)
		return (0);
	return (1);
}
