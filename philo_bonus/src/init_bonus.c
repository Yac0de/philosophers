/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 19:16:39 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 19:15:34 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	create_semaphore_name(char *sem_name, const char *base, int id)
{
	int	i;
	int	j;
	int	id_copy;
	int	length;

	i = -1;
	while (base[++i])
		sem_name[i] = base[i];
	id_copy = id;
	length = 0;
	while (id_copy)
	{
		length++;
		id_copy /= 10;
	}
	id_copy = id;
	j = 0;
	while (j < length)
	{
		sem_name[i + length - j - 1] = (id_copy % 10) + '0';
		id_copy /= 10;
		j++;
	}
	sem_name[i + length] = '\0';
}

static void	init_semaphore(sem_t **sem, char *base_name, int id, int value)
{
	char	sem_name[256];

	create_semaphore_name(sem_name, base_name, id);
	sem_unlink(sem_name);
	*sem = sem_open(sem_name, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		print_error_and_exit("Error\nSem_open failed\n");
}

static void	init_philo_struct(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		data->philos[i].max_meals = false;
		data->philos[i].stop_update_last_meal_time = false;
		init_semaphore(&data->philos[i].sem_eat, "/sem_eat_", i + 1, 1);
		init_semaphore(&data->philos[i].sem_last_meal_time,
			"/sem_last_meal_time_", i + 1, 0);
		init_semaphore(&data->philos[i].sem_stop_update_last_meal_time,
			"/sem_stop_update_last_meal_time_", i + 1, 1);
		init_semaphore(&data->philos[i].sem_last_meal_time_protect,
			"/sem_last_meal_time_protect_", i + 1, 1);
		init_semaphore(&data->philos[i].sem_max_meals, "/sem_max_meals_", i + 1,
			1);
		data->philos[i].data = data;
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
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		print_error_and_exit("Error\nMalloc data->philos failed\n");
	init_semaphore(&data->sem_write, "/sem_write", 0, 1);
	init_semaphore(&data->sem_forks, "/sem_forks", 0, data->nb_philo);
	init_semaphore(&data->sem_death, "/sem_death", 0, 0);
}

void	init_structs(t_data *data, int argc, char **argv)
{
	init_data_struct(data, argc, argv);
	init_philo_struct(data);
}
