/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:59:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/06/07 20:57:21 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_safe_malloc(size_t bytes)
{
	void	*ret;
		
	ret = malloc(bytes);
	if (!ret)
		error_exit("Error with malloc");
	return (ret);
}

static void handle_mutex_error(int status, t_opcode opcode)
{
	if (!status)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	if (status == EDEADLK)
		error_exit("A deadlock would occur if the blocked waiting for mutex");
	if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create another mutex");
	if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else 
		error_exit("WRONG OPCODE FOR MUTEX HANDLE");
}

static void handle_thread_error(int status, t_opcode opcode)
{
	if (!status)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread");
	if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n");
	if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable\n");
	if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
					"specified by the given thread ID, thread.");
	if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
					"thread specifies the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), 
			void *data,t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else 
		error_exit("WRONG OPCODE FOR THREAD HANDLE"
			"Usage: <CREATE> <JOIN> <DETACH>");
}
