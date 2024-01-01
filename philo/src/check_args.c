/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymeziane <ymeziane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:04:12 by ymeziane          #+#    #+#             */
/*   Updated: 2024/01/23 18:56:02 by ymeziane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	validate_argument_count(int argc)
{
	if (argc < 5 || argc > 6)
		print_error_and_exit("Error\nWrong number of arguments\n"
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat"
			" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

static void	validate_positive_value(long int value, int arg_index)
{
	if (value <= 0)
	{
		if (arg_index == 1)
			print_error_and_exit("Error\n"
				"Number of philosophers must be greater than 0\n");
		if (arg_index == 2)
			print_error_and_exit("Error\n"
				"Time to die must be greater than 0\n");
		if (arg_index == 3)
			print_error_and_exit("Error\n"
				"Time to eat must be greater than 0\n");
		if (arg_index == 4)
			print_error_and_exit("Error\n"
				"Time to sleep must be greater than 0\n");
		if (arg_index == 5)
			print_error_and_exit("Error\nNumber of times"
				" each philosopher must eat must be greater than 0\n");
	}
}

static void	validate_whole_number(char *value)
{
	int	i;

	if (!value)
		return ;
	i = 0;
	if (value[i] == '-' || value[i] == '+')
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			print_error_and_exit("Error\nArguments must be whole numbers\n");
		i++;
	}
}

static void	validate_within_int_range(long value, int arg_index)
{
	if (value > INT_MAX || value < INT_MIN)
	{
		if (arg_index == 1)
			print_error_and_exit("Error\n"
				"Number of philosophers must be within int range\n");
		if (arg_index == 2)
			print_error_and_exit("Error\n"
				"Time to die must be within int range\n");
		if (arg_index == 3)
			print_error_and_exit("Error\n"
				"Time to eat must be within int range\n");
		if (arg_index == 4)
			print_error_and_exit("Error\n"
				"Time to sleep must be within int range\n");
		if (arg_index == 5)
			print_error_and_exit("Error\n Number of times each"
				" philosophermust eat must be within int range\n");
	}
}

void	check_args(int argc, char **argv)
{
	int		i;
	long	value;

	validate_argument_count(argc);
	i = 1;
	while (i < argc)
	{
		validate_whole_number(argv[i]);
		value = ft_atol(argv[i]);
		validate_positive_value(value, i);
		validate_within_int_range(value, i);
		i++;
	}
}
