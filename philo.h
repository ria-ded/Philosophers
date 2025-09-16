/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:20:22 by mdziadko          #+#    #+#             */
/*   Updated: 2025/09/15 23:09:59 by mdziadko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>

# define RESET "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

struct	s_data;
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philo;
	int				id;
	int				fork_id[2];
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_lock;
	size_t			last_meal;
	pthread_mutex_t	last_meal_lock;
}				t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				must_eat;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_t		monitor;
	pthread_mutex_t	log_lock;
	size_t			t_start;
	bool			stop_flag;
	pthread_mutex_t	stop_lock;
}					t_data;

// INIT
t_data		*init_data(int argc, char **argv);
int			init_forks(t_data *data);
int			init_philosophers(t_data *data);
void		assign_forks(t_philo *philo, int nb_of_philosophers);

// SIMULATION
bool		simulation_stopped(t_data *data);
int			start_simulation(t_data *data);
int			wait_simulation(t_data *data);
int			join_philosophers(t_data *data, int nb_of_philo);

// ROUTINE
void		take_forks(t_philo *philo);
void		eat(t_philo *philo, size_t monitor_delay);
void		release_forks(t_philo *philo);
void		sleep_and_think(t_philo *philo, size_t monitor_delay);
void		*routine(void *attr);

// MONITORING
size_t		get_time(void);
void		stop_simulation(t_data *data);
bool		is_dead(t_philo *philo);
bool		is_full(t_philo *philo);
void		*monitoring(void *attr);

// PRINT
void		print_log(size_t timestamp, t_philo *philo, char *msg);

// HELP
bool		is_number(char *str);
long long	ft_atoll(char *str);
bool		input_is_valid(int argc, char **argv);
size_t		min(size_t n1, size_t n2);
size_t		time_us(size_t time_ms);

// CLEANUP
void		destroy_philosophers(t_data *data, int nb_of_philosophers);
void		destroy_forks(t_data *data, int nb_of_forks);
void		destroy_simulation(t_data *data);

#endif
