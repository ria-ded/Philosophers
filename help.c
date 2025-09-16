/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:48:59 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/15 22:47:23 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_number(char *str)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		digits++;
		i++;
	}
	return (digits > 0);
}

long long	ft_atoll(char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n'
			|| str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

bool	input_is_valid(int argc, char **argv)
{
	int			i;
	long long	value;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (false);
		value = ft_atoll(argv[i]);
		if (value <= 0 || value > 2147483647)
			return (false);
		i++;
	}
	return (true);
}

size_t	min(size_t n1, size_t n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

size_t	time_us(size_t time_ms)
{
	return (time_ms * 1000);
}
