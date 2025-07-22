/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettersAndSetters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:07:00 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/07/22 14:17:23 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;
	
	safe_mutex_handle(mtx, LOCK);
	ret = *value;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mtx, long *dest, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = value;
	safe_mutex_handle(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;
	
	safe_mutex_handle(mtx, LOCK);
	ret = *value;
	safe_mutex_handle(mtx, UNLOCK);
	return (ret);
}

inline bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
