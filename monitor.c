/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:40:39 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/16 10:37:06 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->stop_lock);
}

bool	is_dead(t_philo *philo)
{
	size_t	timestamp;
	bool	is_dead;
	size_t	meal_start;

	is_dead = false;
	pthread_mutex_lock(&philo->last_meal_lock);
	meal_start = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	timestamp = get_time();
	if (timestamp - meal_start >= philo->data->t_die)
	{
		stop_simulation(philo->data);
		print_log(timestamp, philo, "died");
		is_dead = true;
	}
	return (is_dead);
}

bool	is_full(t_philo *philo)
{
	bool	is_full;

	if (philo->data->must_eat < 0)
		return (false);
	pthread_mutex_lock(&philo->meals_eaten_lock);
	is_full = (philo->meals_eaten >= philo->data->must_eat);
	pthread_mutex_unlock(&philo->meals_eaten_lock);
	return (is_full);
}

void	*monitoring(void *attr)
{
	t_data	*data;
	int		i;
	int		nb_of_full_philo;

	data = attr;
	while (!simulation_stopped(data))
	{
		i = 0;
		nb_of_full_philo = 0;
		while (i < data->nb_of_philo)
		{
			if (is_dead(&data->philo[i]))
				return (NULL);
			if (data->must_eat > 0 && is_full(&data->philo[i]))
				nb_of_full_philo++;
			i++;
		}
		if (data->must_eat > 0 && nb_of_full_philo == data->nb_of_philo)
		{
			stop_simulation(data);
			return (NULL);
		}
		usleep(min(1000, time_us(data->t_die) / 10));
	}
	return (NULL);
}
