/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:11:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/08/11 18:10:23 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char *av[])
{
	t_table	table;
	if (ac != 5 && ac != 6)
		error_exit(RED"WRONG INPUT:\n\t"RESET
					GREEN"Usage: ./philo 5 800 200 200 [5]"RESET);
	parsing(&table, av);
	data_init(&table);
	dinner(&table);
	clean(&table);
}
