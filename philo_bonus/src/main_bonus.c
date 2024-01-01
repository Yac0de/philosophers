/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:46:03 by ymeziane          #+#    #+#             */
/*   Updated: 2025/02/04 17:01:56 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	create_pid_for_each_philo(t_data *data)
{
	size_t	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].pid_life = fork();
		if (data->philos[i].pid_life == -1)
			print_error_and_exit("Error\nfork failed\n");
		else if (data->philos[i].pid_life == 0)
		{
			philosopher_routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		data->philos[i].pid_death = fork();
		if (data->philos[i].pid_death == -1)
			print_error_and_exit("Error\nfork failed\n");
		else if (data->philos[i].pid_death == 0)
		{
			check_philosopher_death(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

static void	wait_end_each_pid(t_data *data)
{
	size_t	i;

	i = 0;
	sem_wait(data->sem_death);
	while (i < data->nb_philo)
	{
		sem_close(data->philos[i].sem_last_meal_time);
		sem_close(data->philos[i].sem_stop_update_last_meal_time);
		sem_close(data->philos[i].sem_eat);
		sem_close(data->philos[i].sem_last_meal_time_protect);
		sem_close(data->philos[i].sem_max_meals);
		kill(data->philos[i].pid_life, SIGKILL);
		kill(data->philos[i].pid_death, SIGKILL);
		waitpid(data->philos[i].pid_life, NULL, 0);
		waitpid(data->philos[i].pid_death, NULL, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	check_args(argc, argv);
	init_structs(&data, argc, argv);
	create_pid_for_each_philo(&data);
	wait_end_each_pid(&data);
	cleanup_resources(&data);
	return (0);
}
