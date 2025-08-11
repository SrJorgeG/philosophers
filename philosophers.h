/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:47:56 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/08/11 18:19:11 by jgomez-d         ###   ########.fr       */
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

 // DEBUG MODE

 #define DEBUG_MODE 0
 
 // THREAD STATES

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

 // TIME STATES 

 typedef enum e_time_code
 {
	SECOND,
	MILISECOND,
	MICROSECOND,
 } t_time_code;
 
 // PREDECLARATIONS OF TABLE AND MUTEX FOR RECURSION
 
 typedef struct s_table t_table;
 
 typedef pthread_mutex_t t_mtx;
 
 // FORKS

 typedef struct s_fork
 {
	t_mtx	fork;
	int		fork_id;
 } t_fork;

 // PHILO

 typedef enum e_philo_status
 {
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
 } t_philo_status;
 
 typedef struct s_philo
 {
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; // TIME PASSED FROM LAST MEAL 
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mtx		philo_mutex;
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
	bool	all_threads_ready;
	long	threads_running_nbr;
	pthread_t	monitor;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
 };

 // UTILS
 
 long	get_time(t_time_code timecode);
 void	error_exit(const char *error);
 void	precise_usleep(t_table *table, long usec);
 void	clean(t_table *table);

 // PARSING

 void	parse_input(t_table *table, char **av);

 // INIT
 
 void	data_init(t_table *table);

 // HANDLERS
 
 void	*ft_safe_malloc(size_t bytes);
 void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
 void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), 
			void *data,t_opcode opcode);
			
 // SYNC UTILS

 void	wait_all_threads(t_table *table); 
 bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
 void	increase_long(t_mtx *mutex, long *value);
 
 // GETTERS AND SETTERS

 void	set_bool(t_mtx *mtx, bool *dest, bool value);
 bool	get_bool(t_mtx *mtx, bool *value);
 void	set_long(t_mtx *mtx, long *dest, long value);
 long	get_long(t_mtx *mtx, long *value);
 inline	bool simulation_finished(t_table *table);

 // WRITING

 void	write_status(t_philo_status status, t_philo *philo, bool debug);
 
 // MONITOR

 void	*monitor_dinner(void *data);

 // DINNER

 void	*dinner_simulation(void *data);
 void	dinner_start(t_table *table);
 void	*lone_philo(void *arg);
 
#endif
