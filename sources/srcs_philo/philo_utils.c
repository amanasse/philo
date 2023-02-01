/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:27:05 by amanasse          #+#    #+#             */
/*   Updated: 2022/10/21 17:10:11 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_printf(char *str, time_t time, int id, t_philo *philo)
{
	if (check_data_death(philo) == 0)
	{	
		pthread_mutex_lock(&philo->d->mutex_print);
		printf(str, time, id);
		pthread_mutex_unlock(&philo->d->mutex_print);
	}	
}

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	long int	i;
	long int	nb;
	int			neg;
	char		*str;

	i = 0;
	nb = 0;
	neg = 1;
	str = (char *)nptr;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (ft_str_is_numeric(&str[i]) == 0)
		return (-1);
	if (str[i] == '-')
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = (nb * 10) + (str[i] - 48);
		if (nb > 2147483647)
			return (-1);
		i++;
	}
	return (nb * neg);
}
