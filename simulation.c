/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:23:53 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/15 23:09:59 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_stopped(t_data *data)
{
	bool	stopped;

	pthread_mutex_lock(&data->stop_lock);
	stopped = data->stop_flag;
	pthread_mutex_unlock(&data->stop_lock);
	return (stopped);
}

int	start_simulation(t_data *data)
{
	int	i;
	int	exit_code;

	data->t_start = get_time();
	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].last_meal = data->t_start;
		exit_code = pthread_create(&data->philo[i].philo, NULL,
				routine, &data->philo[i]);
		if (exit_code)
		{
			join_philosophers(data, i);
			return (exit_code);
		}
		i++;
	}
	exit_code = pthread_create(&data->monitor, NULL, monitoring, data);
	if (exit_code)
	{
		join_philosophers(data, data->nb_of_philo);
		return (exit_code);
	}
	return (0);
}

int	wait_simulation(t_data *data)
{
	pthread_join(data->monitor, NULL);
	join_philosophers(data, data->nb_of_philo);
	return (0);
}

int	join_philosophers(t_data *data, int nb_of_philo)
{
	int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		pthread_join(data->philo[i].philo, NULL);
		i++;
	}
	return (0);
}
