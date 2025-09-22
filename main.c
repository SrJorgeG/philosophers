/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:11:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/09/22 12:20:09 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char *av[])
{
	t_table	table;
	if (!(ac == 5 || ac == 6))
		error_exit(RED"WRONG INPUT:\n\t"RESET
					GREEN"Usage: ./philo 5 800 200 200 [5]"RESET);
	parse_input(&table, av);
	data_init(&table);
	dinner_start(&table);
	clean(&table);
}
