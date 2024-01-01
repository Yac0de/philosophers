/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:22:48 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 19:15:15 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

static void	little_printf_int(const char *str, int num)
{
	while (*str)
	{
		if ((*str == '%') && (*(str + 1) == 'd' || *(str + 1) == 'i'))
		{
			ft_putnbr(num);
			str++;
		}
		else
			write(1, str, 1);
		str++;
	}
}

static void	choose_color(const char *str, const char **color)
{
	if (ft_strcmp(str, "has died") == 0)
		*color = "\033[31m";
	else if (ft_strcmp(str, "is sleeping") == 0)
		*color = "\033[34m";
	else if (ft_strcmp(str, "is eating") == 0)
		*color = "\033[33m";
	else if (ft_strcmp(str, "is thinking") == 0)
		*color = "\033[32m";
	else
		*color = "\033[0m";
}

void	updated_and_print_timestamp(t_data *data, const char *str,
		unsigned int id)
{
	const char	*color;
	int			current_time;

	choose_color(str, &color);
	current_time = get_time() - data->start_time;
	sem_wait(data->sem_write);
	little_printf_int("%d ", current_time);
	little_printf_int("%d ", id);
	write(1, color, ft_strlen(color));
	write(1, str, ft_strlen(str));
	write(1, "\033[0m\n", 5);
	if (ft_strcmp(str, "died") != 0)
		sem_post(data->sem_write);
}

void	print_error_and_exit(const char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}
