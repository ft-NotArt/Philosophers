/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:54:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/09 00:09:22 by anoteris         ###   ########.fr       */
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
