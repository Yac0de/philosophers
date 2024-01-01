/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:04:48 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:35:06 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->mutex_right_fork < philo->mutex_left_fork)
	{
		first_fork = philo->mutex_right_fork;
		second_fork = philo->mutex_left_fork;
	}
	else
	{
		first_fork = philo->mutex_left_fork;
		second_fork = philo->mutex_right_fork;
	}
	pthread_mutex_lock(first_fork);
	updated_and_print_timestamp(philo->data, "has taken a fork", philo->id);
	if (philo->data->nb_philo == 1)
		return (ft_usleep(philo->data->time_to_die + 2));
	pthread_mutex_lock(second_fork);
	updated_and_print_timestamp(philo->data, "has taken a fork", philo->id);
}

static void	philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_eat);
	updated_and_print_timestamp(philo->data, "is eating", philo->id);
	pthread_mutex_lock(&philo->mutex_nb_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->mutex_nb_eat);
	pthread_mutex_lock(&philo->mutex_last_meal_time);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal_time);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->mutex_eat);
}

static void	put_forks(t_philo *philo)
{
	if (philo->data->nb_philo > 1)
		pthread_mutex_unlock(philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
}

static void	philosopher_sleep_and_think(t_philo *philo)
{
	updated_and_print_timestamp(philo->data, "is sleeping", philo->id);
	ft_usleep(philo->data->time_to_sleep);
	updated_and_print_timestamp(philo->data, "is thinking", philo->id);
}

bool	actions(t_philo *philo)
{
	take_forks(philo);
	philosopher_eat(philo);
	put_forks(philo);
	if (check_max_meals(philo))
		return (false);
	philosopher_sleep_and_think(philo);
	return (true);
}
