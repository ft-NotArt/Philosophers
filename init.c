/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:11:18 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/08 21:16:20 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*init_args(int argc, char *argv[])
{
	t_args	*args ;

	args = malloc(sizeof(t_args));
	args->nb_philo = atol(argv[1]);
	args->time_to_die = atol(argv[2]);
	args->time_to_eat = atol(argv[3]);
	args->time_to_sleep = atol(argv[4]);
	if (argc == 6)
		args->nb_time_must_eat = atol(argv[5]);
	else
		args->nb_time_must_eat = -1 ;
	return (args);
}
