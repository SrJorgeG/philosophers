/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:58:12 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/07/22 14:09:01 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_num;
	
	philo_num = philo->table->philo_num;
	if (!(philo->id % 2))
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_num];
	} else
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_num];
		philo->second_fork = &forks[philo_position];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
	}
}

void	data_init(t_table *table)
{
	int i;
	
	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = ft_safe_malloc(sizeof(t_philo) * table->philo_num);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->forks = ft_safe_malloc(sizeof(t_fork) * table->philo_num);
	while (++i < table->philo_num)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
