/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:54:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/13 20:12:57 by anoteris         ###   ########.fr       */
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

void	error_fork(t_table *table)
{
	sem_wait(table->display);
	write(STDERR_FILENO, "fork failed\n", 13);
	sem_post(table->display);
}

void	error_pthread(t_table *table)
{
	write(STDERR_FILENO, "Pthread create/join failed\n", 28);
	sem_wait(table->death);
}
