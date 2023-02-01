/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:38:34 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/21 16:09:12 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_destroy(t_philo *philo, t_data *data)
{
	int	j;

	j = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_control);
	pthread_mutex_destroy(&data->mutex_time);
	pthread_mutex_destroy(&data->mutex_nb_of_philo);
	while (j < data->n_of_philo)
	{
		pthread_mutex_destroy(&data->mutex_forks[j]);
		j++;
	}
	free(philo);
}

void	ft_end_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (philo)
		ft_destroy(philo, data);
}
