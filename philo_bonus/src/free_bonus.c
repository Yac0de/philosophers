/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:24:14 by ymeziane          #+#    #+#             */
/*   Updated: 2025/02/04 17:04:22 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	generate_sem_name(char *buffer, const char *base, int id)
{
	int		i;
	int		j;
	int		num;
	char	tmp[12];

	i = 0;
	num = id;
	while (base[i])
	{
		buffer[i] = base[i];
		i++;
	}
	j = 0;
	if (num == 0)
		tmp[j++] = '0';
	while (num > 0)
	{
		tmp[j++] = (num % 10) + '0';
		num /= 10;
	}
	while (j > 0)
		buffer[i++] = tmp[--j];
	buffer[i] = '\0';
}

void	cleanup_resources(t_data *data)
{
	unsigned int	i;
	char			sem_name[50];

	i = 0;
	sem_close(data->sem_write);
	sem_unlink("/sem_write");
	sem_close(data->sem_forks);
	sem_unlink("/sem_forks");
	sem_close(data->sem_death);
	sem_unlink("/sem_death");
	while (i < data->nb_philo)
	{
		generate_sem_name(sem_name, "/sem_eat_", i + 1);
		sem_unlink(sem_name);
		generate_sem_name(sem_name, "/sem_last_meal_time_", i + 1);
		sem_unlink(sem_name);
		generate_sem_name(sem_name, "/sem_stop_update_last_meal_time_", i + 1);
		sem_unlink(sem_name);
		generate_sem_name(sem_name, "/sem_last_meal_time_protect_", i + 1);
		sem_unlink(sem_name);
		generate_sem_name(sem_name, "/sem_max_meals_", i + 1);
		sem_unlink(sem_name);
		i++;
	}
	free(data->philos);
}
