/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:03:20 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/09/23 23:23:08 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;
	
	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);	
	elapsed = get_time(MILISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;
	long	all_full;
	
	table = (t_table *)data;
	while (!simulation_finished(table))
	{
		i = -1;
		all_full = 0;
		while (++i < table->philo_num && !simulation_finished(table))
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			} else if (get_bool(&table->philos[i].philo_mutex, &table->philos[i].full))
				all_full++;
		if (all_full == table->philo_num)
			(printf("All end/n\n") , set_bool(&table->table_mutex, &table->end_simulation, true));
		usleep(100);
	}
	return (NULL);
}
