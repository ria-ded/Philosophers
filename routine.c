/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:07:14 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/16 14:05:36 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->fork_id[0]]);
	print_log(get_time(), philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->fork_id[1]]);
	print_log(get_time(), philo, "has taken a fork");
}

void	eat(t_philo *philo, size_t monitor_delay)
{
	size_t	time_spent;
	size_t	meal_start;

	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time();
	meal_start = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	print_log(meal_start, philo, "is eating");
	while (!simulation_stopped(philo->data))
	{
		time_spent = get_time() - meal_start;
		if (time_spent >= philo->data->t_eat)
			break ;
		usleep(monitor_delay);
	}
	pthread_mutex_lock(&philo->meals_eaten_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_lock);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->fork_id[0]]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_id[1]]);
}

void	sleep_and_think(t_philo *philo, size_t monitor_delay)
{
	size_t	time_spent;
	size_t	time_since_meal;
	size_t	timestamp;

	timestamp = get_time();
	print_log(timestamp, philo, "is sleeping");
	while (!simulation_stopped(philo->data))
	{
		time_spent = get_time() - timestamp;
		if (time_spent >= philo->data->t_sleep)
			break ;
		usleep(monitor_delay);
	}
	timestamp = get_time();
	print_log(timestamp, philo, "is thinking");
	pthread_mutex_lock(&philo->last_meal_lock);
	time_since_meal = timestamp - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (philo->data->t_die - time_since_meal > 10)
		usleep(min(1000,
				(time_us(philo->data->t_eat + philo->data->t_sleep)) / 50));
}

void	*routine(void *attr)
{
	t_philo	*philo;
	size_t	monitor_delay;

	philo = (t_philo *)attr;
	monitor_delay = min(1000, time_us(philo->data->t_die) / 10);
	if (philo->data->nb_of_philo == 1)
	{
		pthread_mutex_lock(&philo->data->fork[philo->fork_id[0]]);
		print_log(get_time(), philo, "has taken a fork");
		pthread_mutex_unlock(&philo->data->fork[philo->fork_id[0]]);
		usleep(time_us(philo->data->t_die));
		return (NULL);
	}
	while (!simulation_stopped(philo->data))
	{
		take_forks(philo);
		eat(philo, monitor_delay);
		release_forks(philo);
		sleep_and_think(philo, monitor_delay);
	}
	return (NULL);
}
