/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:00:06 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/16 09:32:51 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


void	print_log(size_t timestamp, t_philo *philo, char *msg)
{
	size_t	time;
	bool	stopped;

	pthread_mutex_lock(&philo->data->log_lock);
	stopped = simulation_stopped(philo->data);
	time = timestamp - philo->data->t_start;
	if (!stopped || ft_strcmp(msg, "died") == 0)
		printf("%zu %i %s\n", time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->log_lock);
}
