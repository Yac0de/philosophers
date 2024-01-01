/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:46:48 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:57:00 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_philo;

typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_must_eat;
	bool			stop_simulation;
	unsigned int	start_time;
	pthread_mutex_t	*mutex_forks_array;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_stop;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread_life_id;
	pthread_t		thread_death_id;
	unsigned int	nb_eat;
	pthread_mutex_t	mutex_nb_eat;
	bool			max_meals;
	pthread_mutex_t	mutex_max_meals;
	pthread_mutex_t	*mutex_left_fork;
	pthread_mutex_t	*mutex_right_fork;
	unsigned int	last_meal_time;
	pthread_mutex_t	mutex_last_meal_time;
	pthread_mutex_t	mutex_eat;
	t_data			*data;
}					t_philo;

// CHECK_ARGS
void				check_args(int argc, char **argv);

// UTILS
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
long				ft_atol(const char *nptr);
unsigned int		get_time(void);
void				ft_usleep(unsigned int time);

// FT_STR
int					ft_strlen(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putstr_fd(const char *s, int fd);

// DISPLAY
void				updated_and_print_timestamp(t_data *data, const char *str,
						unsigned int id);
void				print_error_and_exit(const char *error_message);

// INIT
void				init_structs(t_data *data, int argc, char **argv);

// ACTIONS
bool				actions(t_philo *philo);

// THREADS_ROUTINE
void				*philosopher_routine(void *arg);
bool				check_max_meals(t_philo *philo);

// THREADS_DEATH
void				*check_philosopher_death(void *arg);

#endif
