/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:46:03 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:50:55 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	create_threads_for_each_philo(t_data *data)
{
	size_t	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread_life_id, NULL,
				&philosopher_routine, &data->philos[i]) != 0)
			print_error_and_exit("Error\npthread_create failed\n");
		if (pthread_create(&data->philos[i].thread_death_id, NULL,
				&check_philosopher_death, &data->philos[i]) != 0)
			print_error_and_exit("Error\npthread_create failed\n");
		i++;
	}
}

static void	wait_end_each_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_life_id, NULL);
		pthread_join(data->philos[i].thread_death_id, NULL);
		i++;
	}
}

static void	cleanup_resources(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->mutex_forks_array[i]);
		pthread_mutex_destroy(&data->philos[i].mutex_nb_eat);
		pthread_mutex_destroy(&data->philos[i].mutex_max_meals);
		pthread_mutex_destroy(&data->philos[i].mutex_last_meal_time);
		pthread_mutex_destroy(&data->philos[i].mutex_eat);
		i++;
	}
	free(data->mutex_forks_array);
	free(data->philos);
	pthread_mutex_destroy(&data->mutex_write);
	pthread_mutex_destroy(&data->mutex_stop);
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_structs(&data, argc, argv);
	create_threads_for_each_philo(&data);
	wait_end_each_threads(&data);
	cleanup_resources(&data);
	return (0);
}
