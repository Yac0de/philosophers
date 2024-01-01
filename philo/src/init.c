/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 19:16:39 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:57:15 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_philo_struct(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		pthread_mutex_init(&data->philos[i].mutex_nb_eat, NULL);
		data->philos[i].max_meals = false;
		pthread_mutex_init(&data->philos[i].mutex_max_meals, NULL);
		data->philos[i].mutex_left_fork = &data->mutex_forks_array[i];
		data->philos[i].mutex_right_fork = &data->mutex_forks_array[(i + 1)
			% data->nb_philo];
		pthread_mutex_init(&data->philos[i].mutex_last_meal_time, NULL);
		pthread_mutex_init(&data->philos[i].mutex_eat, NULL);
		data->philos[i].data = data;
		i++;
	}
}

static void	init_mutex_fork(t_data *data)
{
	size_t	i;

	data->mutex_forks_array = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nb_philo);
	if (!data->mutex_forks_array)
		print_error_and_exit("Error\nMalloc data->mutex_forks_array failed\n");
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->mutex_forks_array[i], NULL);
		i++;
	}
}

static void	init_data_struct(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	data->stop_simulation = false;
	init_mutex_fork(data);
	pthread_mutex_init(&data->mutex_write, NULL);
	pthread_mutex_init(&data->mutex_stop, NULL);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		print_error_and_exit("Error\nMalloc data->philos failed\n");
}

void	init_structs(t_data *data, int argc, char **argv)
{
	init_data_struct(data, argc, argv);
	init_philo_struct(data);
}
