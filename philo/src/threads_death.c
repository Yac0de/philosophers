/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:16:59 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:49:03 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	check_time_to_die(t_philo *philo)
{
	unsigned int	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->mutex_last_meal_time);
	pthread_mutex_lock(&philo->mutex_max_meals);
	if (current_time - philo->last_meal_time > philo->data->time_to_die
		&& !philo->max_meals)
	{
		pthread_mutex_unlock(&philo->mutex_last_meal_time);
		pthread_mutex_unlock(&philo->mutex_max_meals);
		updated_and_print_timestamp(philo->data, "died", philo->id);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_max_meals);
	pthread_mutex_unlock(&philo->mutex_last_meal_time);
	return (false);
}

void	*check_philosopher_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		ft_usleep(philo->data->time_to_die + 1);
		pthread_mutex_lock(&philo->mutex_max_meals);
		if (philo->max_meals)
		{
			pthread_mutex_unlock(&philo->mutex_max_meals);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex_max_meals);
		pthread_mutex_lock(&philo->mutex_eat);
		if (check_time_to_die(philo))
			return (pthread_mutex_unlock(&philo->mutex_eat), NULL);
		pthread_mutex_unlock(&philo->mutex_eat);
	}
	return (NULL);
}
