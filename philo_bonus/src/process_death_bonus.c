/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_death_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:16:59 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 19:15:58 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_time_to_die(t_philo *philo)
{
	unsigned int	current_time;

	current_time = get_time();
	sem_wait(philo->sem_last_meal_time_protect);
	if (current_time - philo->last_meal_time > philo->data->time_to_die
		&& !philo->max_meals)
	{
		sem_post(philo->sem_last_meal_time_protect);
		sem_post(philo->sem_last_meal_time);
		updated_and_print_timestamp(philo->data, "died", philo->id);
		return (true);
	}
	sem_post(philo->sem_last_meal_time_protect);
	return (false);
}

static void	*update_last_meal_time(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		sem_wait(philo->sem_stop_update_last_meal_time);
		if (philo->stop_update_last_meal_time)
			return (sem_post(philo->sem_stop_update_last_meal_time), NULL);
		sem_post(philo->sem_stop_update_last_meal_time);
		sem_wait(philo->sem_last_meal_time);
		sem_wait(philo->sem_last_meal_time_protect);
		philo->last_meal_time = get_time();
		sem_post(philo->sem_last_meal_time_protect);
		philo->nb_eat++;
		sem_wait(philo->sem_max_meals);
		if (check_max_meals(philo))
			return (sem_post(philo->sem_max_meals), NULL);
		sem_post(philo->sem_max_meals);
		ft_usleep(100);
	}
	return (NULL);
}

void	*check_philosopher_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_create(&philo->thread_last_meal_time_id, NULL,
		&update_last_meal_time, philo);
	while (true)
	{
		ft_usleep(philo->data->time_to_die + 1);
		sem_wait(philo->sem_eat);
		sem_wait(philo->sem_max_meals);
		if (check_time_to_die(philo) || philo->max_meals)
		{
			sem_post(philo->sem_max_meals);
			sem_wait(philo->sem_stop_update_last_meal_time);
			philo->stop_update_last_meal_time = true;
			sem_post(philo->sem_stop_update_last_meal_time);
			pthread_join(philo->thread_last_meal_time_id, NULL);
			sem_post(philo->data->sem_death);
			return (NULL);
		}
		sem_post(philo->sem_max_meals);
		sem_post(philo->sem_eat);
	}
	return (NULL);
}
