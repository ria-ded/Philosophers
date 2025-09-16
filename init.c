/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:37:13 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/15 22:32:12 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, int nb_of_philosophers)
{
	if (philo->id % 2 == 0)
	{
		philo->fork_id[0] = philo->id;
		philo->fork_id[1] = (philo->id + 1) % nb_of_philosophers;
	}
	else
	{
		philo->fork_id[0] = (philo->id + 1) % nb_of_philosophers;
		philo->fork_id[1] = philo->id;
	}
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return (1);
	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i;
		assign_forks(&data->philo[i], data->nb_of_philo);
		data->philo[i].meals_eaten = 0;
		if (pthread_mutex_init(&data->philo[i].meals_eaten_lock, NULL)
			|| pthread_mutex_init(&data->philo[i].last_meal_lock, NULL))
		{
			destroy_philosophers(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->fork = malloc(
			sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		return (1);
	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			destroy_forks(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mtx_and_struct(t_data *data)
{
	if (init_philosophers(data))
		return (1);
	if (init_forks(data))
	{
		destroy_philosophers(data, data->nb_of_philo);
		return (1);
	}
	if (pthread_mutex_init(&data->log_lock, NULL))
	{
		destroy_philosophers(data, data->nb_of_philo);
		destroy_forks(data, data->nb_of_philo);
		return (1);
	}
	if (pthread_mutex_init(&data->stop_lock, NULL))
	{
		destroy_philosophers(data, data->nb_of_philo);
		destroy_forks(data, data->nb_of_philo);
		pthread_mutex_destroy(&data->log_lock);
		return (1);
	}
	return (0);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_of_philo = ft_atoll(argv[1]);
	data->t_die = ft_atoll(argv[2]);
	data->t_eat = ft_atoll(argv[3]);
	data->t_sleep = ft_atoll(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoll(argv[5]);
	data->stop_flag = false;
	if (init_mtx_and_struct(data))
	{
		free (data);
		return (NULL);
	}
	return (data);
}
