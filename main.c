/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:20:18 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/15 23:03:51 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!input_is_valid(argc, argv))
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (1);
	if (start_simulation(data))
	{
		destroy_simulation(data);
		return (1);
	}
	wait_simulation(data);
	destroy_simulation(data);
	return (0);
}
