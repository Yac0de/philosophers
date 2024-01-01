/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:46:48 by ymeziane          #+#    #+#             */
/*   Updated: 2025/02/04 17:02:02 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
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
	sem_t			*sem_write;
	sem_t			*sem_forks;
	sem_t			*sem_death;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	unsigned int	id;
	pid_t			pid_life;
	pid_t			pid_death;
	pthread_t		thread_last_meal_time_id;
	unsigned int	nb_eat;
	bool			max_meals;
	unsigned int	last_meal_time;
	bool			stop_update_last_meal_time;
	sem_t			*sem_last_meal_time;
	sem_t			*sem_last_meal_time_protect;
	sem_t			*sem_stop_update_last_meal_time;
	sem_t			*sem_eat;
	sem_t			*sem_max_meals;
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

// FREE
void				cleanup_resources(t_data *data);

#endif
