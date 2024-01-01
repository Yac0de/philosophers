/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:04:48 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 12:07:58 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	updated_and_print_timestamp(philo->data, "has taken a fork", philo->id);
	sem_wait(philo->data->sem_forks);
	updated_and_print_timestamp(philo->data, "has taken a fork", philo->id);
}

static void	philosopher_eat(t_philo *philo)
{
	sem_wait(philo->sem_eat);
	updated_and_print_timestamp(philo->data, "is eating", philo->id);
	philo->nb_eat++;
	sem_post(philo->sem_last_meal_time);
	philo->last_meal_time = get_time();
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->sem_eat);
}

static void	put_forks(t_philo *philo)
{
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
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
