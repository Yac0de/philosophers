/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:06:39 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:30:22 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_max_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_max_meals);
	pthread_mutex_lock(&philo->mutex_nb_eat);
	if (!philo->max_meals && philo->data->nb_must_eat != -1
		&& philo->nb_eat == (unsigned int)philo->data->nb_must_eat)
	{
		pthread_mutex_unlock(&philo->mutex_nb_eat);
		philo->max_meals = true;
		pthread_mutex_unlock(&philo->mutex_max_meals);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_max_meals);
	pthread_mutex_unlock(&philo->mutex_nb_eat);
	return (false);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while (true)
	{
		pthread_mutex_lock(&philo->data->mutex_stop);
		if (philo->data->stop_simulation)
			return (pthread_mutex_unlock(&philo->data->mutex_stop), NULL);
		pthread_mutex_unlock(&philo->data->mutex_stop);
		if (!actions(philo))
			return (NULL);
	}
	return (NULL);
}
