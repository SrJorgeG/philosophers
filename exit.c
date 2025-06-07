/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:17:38 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/06/07 15:30:30 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(const char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}
