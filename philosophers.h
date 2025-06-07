/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:47:56 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/06/07 21:18:58 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
 #define PHILOSOPHERS_H

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <stdbool.h>
 #include <pthread.h>
 #include <sys/time.h>
 #include <limits.h>
 #include <errno.h>

 // ANSI ESCAPE SEQUENCES
 
 #define RESET		"\x1b[0m"
 #define BLACK		"\x1b[30m"
 #define RED		"\x1b[31m"
 #define GREEN		"\x1b[32m"
 #define YELLOW		"\x1b[33m"
 #define BLUE		"\x1b[34m"
 #define MAGENTA	"\x1b[35m"
 #define CYAN		"\x1b[36m"
 #define WHITE		"\x1b[37m"

 typedef enum e_opcode
 {
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
 } t_opcode;
 
 // PREDECLARATION OF THE TABLE FOR RECURSION
 
 typedef struct s_table t_table;
 
 // FORKS

 typedef pthread_mutex_t t_mtx;

 typedef struct s_fork
 {
	t_mtx	fork;
	int		fork_id;
 } t_fork;

 // PHILO

 typedef struct s_philo
 {
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; // TIME PASSED FROM LAST MEAL 
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
 } t_philo;
 
 // TABLE

 struct s_table
 {
	long	philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_slp;
	long	limit_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
 };

 // EXIT

 void	error_exit(const char *error);

 // PARSING

 void	parse_input(t_table *table, char **av);

 // INIT
 
 void	data_init(t_table *table);

 // UTILS
 
 void	*ft_safe_malloc(size_t bytes);
 void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
 void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), 
			void *data,t_opcode opcode);

#endif
