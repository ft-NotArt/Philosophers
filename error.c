/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:54:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/12 01:17:57 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_args(void)
{
	write(STDERR_FILENO, "Philo args :\
	\n\t(uint) number_of_philosophers (strictly positive)\
	\n\t(uint) time_to_die (strictly positive)\
	\n\t(uint) time_to_eat (strictly positive)\
	\n\t(uint) time_to_sleep (strictly positive)\
	\n\t(uint) [number_of_times_each_philosopher_must_eat] (strictly positive)\
	\n", 265);
}

void	error_pthread(t_table *table)
{
	write(STDERR_FILENO, "Pthread create/join failed\n", 28);
	pthread_mutex_lock(&table->mutex_update);
	table->state = PTHREAD_FAIL ;
	pthread_mutex_unlock(&table->mutex_update);
}
