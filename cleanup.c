/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:19:47 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/13 11:20:27 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philosophers(t_data *data, int nb_of_philosophers)
{
	int	i;

	if (!data || !data->philo)
		return ;
	i = 0;
	while (i < nb_of_philosophers)
	{
		pthread_mutex_destroy(&data->philo[i].meals_eaten_lock);
		pthread_mutex_destroy(&data->philo[i].last_meal_lock);
		i++;
	}
	free(data->philo);
	data->philo = NULL;
}

void	destroy_forks(t_data *data, int nb_of_forks)
{
	int	i;

	if (!data || !data->fork)
		return ;
	i = 0;
	while (i < nb_of_forks)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	data->fork = NULL;
}

void	destroy_simulation(t_data *data)
{
	if (!data)
		return ;
	destroy_philosophers(data, data->nb_of_philo);
	destroy_forks(data, data->nb_of_philo);
	pthread_mutex_destroy(&data->log_lock);
	pthread_mutex_destroy(&data->stop_lock);
	free(data);
}
