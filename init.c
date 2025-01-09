/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:11:18 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/09 07:33:31 by anoteris         ###   ########.fr       */
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

t_table	*init_table(void)
{
	t_table	*table ;

	table = malloc(sizeof(t_table));
	if (pthread_mutex_init(&table->mutex_update, NULL) != 0)
	{
		free(table);
		write(STDERR_FILENO, "Mutex init failed\n", 19);
		return (NULL);
	}
	table->state = ENJOY_YOUR_MEAL ;
	table->nb_fullfilled_philos = 0 ;
	return (table);
}

t_philo	*init_philo(t_args *args, t_table *table, int id,
	pthread_mutex_t *left_fork)
{
	t_philo	*philo ;

	philo = malloc(sizeof(t_philo));
	philo->args = args ;
	philo->table = table ;
	philo->id = id ;
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
	{
		free(philo);
		write(STDERR_FILENO, "Mutex init failed\n", 19);
		return (NULL);
	}
	philo->left_fork = left_fork ;
	philo->nb_time_ate = 0 ;
	return (philo);
}
