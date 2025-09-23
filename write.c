/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 00:28:35 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/09/23 23:13:41 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf(WHITE"%-6ld"RESET YELLOW" PHILO:[%d] has taken the 1st FORK:[%d]\n"RESET, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf(WHITE"%-6ld"RESET MAGENTA" PHILO:[%d] has taken the 2nd FORK:[%d]\n"RESET, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(WHITE"%-6ld"RESET GREEN" PHILO:[%d] is eating, MEALS:[%ld]\n"RESET, elapsed, philo->id,
			philo->meals_counter + 1);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(WHITE"%-6ld"RESET BLUE" PHILO:[%d] is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(WHITE"%-6ld"RESET  CYAN" PHILO:[%d] is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIED)
		printf(WHITE"%-6ld"RESET RED" PHILO:[%d] died\n"RESET, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;
	
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	elapsed = get_time(MILISECOND) - philo->table->start_simulation;
	if (debug)
		write_status_debug(status, philo, elapsed);	
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf(WHITE"%-6ld"RESET" PHILO:[%d] has taken a fork\n"RESET, elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf(WHITE"%-6ld"RESET" PHILO:[%d] is eating\n"RESET, elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf(WHITE"%-6ld"RESET" PHILO:[%d] is sleeping\n"RESET, elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf(WHITE"%-6ld"RESET" PHILO:[%d] is thinking\n"RESET, elapsed, philo->id);
		else if (status == DIED)
			printf(WHITE"%-6ld"RESET" PHILO:[%d] died\n"RESET, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);	
}
