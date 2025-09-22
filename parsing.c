/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:35:57 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/09/22 12:25:34 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static	inline bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char *valid_input(const char *str)
{
	int	len;
	const char	*number;

	len = 0;
	if (!str)
		return (NULL);	
	while (is_space(*str))
		++str;
	if(*str == '-')
		error_exit("WRONG INPUT: CAN'T TAKE NEGATIVES");
	if(*str == '+')
		++str;
	if (!is_digit(*str))
		error_exit("WRONG INPUT: NOT A CORRECT NUMBER");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("WRONG INPUT: NUMBER TOO LONG");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
		return (0);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("WRONG INPUT: NUMBER TOO LARGE");
	return (num);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_num = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_slp = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_slp < 6e4)
		error_exit("WRONG INPUT: USE TIMESTAMPS MAJOR THAN 60ms");
	if (av[5])
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
}
