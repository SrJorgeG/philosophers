/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:59:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/09/22 17:23:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if (status == EAGAIN)
        error_exit("The system lacked the necessary resources (other than memory) to initialize another mutex");
	if (status == ENOTRECOVERABLE)
        error_exit("The state protected by the mutex is not recoverable.	");
	if (status == EOWNERDEAD)
		error_exit("The previous owner of this mutex died while holding the mutex");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	int status = 0;
	
	if (opcode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else 
		error_exit("WRONG OPCODE FOR MUTEX HANDLE");
	handle_mutex_error(status, opcode);
}

static void handle_thread_error(int status, t_opcode opcode)
{
	if (!status)
		return ;
	if (status == EAGAIN)
		error_exit("Insufficient resources to create another thread");
	if (status == EPERM)
		error_exit("The caller does not have appropriate permission\n");
	if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable\n");
	if (status == ESRCH)
		error_exit("No thread could be found corresponding to that"
					"specified by the given thread ID.");
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
