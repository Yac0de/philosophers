/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routine_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:06:39 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/22 13:17:44 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_max_meals(t_philo *philo)
{
	if (!philo->max_meals && philo->data->nb_must_eat != -1
		&& philo->nb_eat == (unsigned int)philo->data->nb_must_eat)
	{
		philo->max_meals = true;
		return (true);
	}
	return (false);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	i = 0;
	while (true)
	{
		if (!actions(philo))
			return (NULL);
		i++;
	}
	return (NULL);
}
