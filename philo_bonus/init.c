/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:11:18 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/15 03:26:50 by anoteris         ###   ########.fr       */
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

t_table	*init_table(t_args *args)
{
	t_table	*table ;

	table = malloc(sizeof(t_table));
	(sem_unlink(SEM_FORK), sem_unlink(SEM_DEATH));
	(sem_unlink(SEM_DISPLAY), sem_unlink(SEM_UPDATE));
	table->forks = sem_open(SEM_FORK, O_CREAT, O_RDWR, args->nb_philo);
	table->death = sem_open(SEM_DEATH, O_CREAT, O_RDWR, 1);
	table->display = sem_open(SEM_DISPLAY, O_CREAT, O_RDWR, 1);
	table->update = sem_open(SEM_UPDATE, O_CREAT, O_RDWR, 1);
	if (table->forks == SEM_FAILED
		|| table->death == SEM_FAILED
		|| table->display == SEM_FAILED
		|| table->update == SEM_FAILED)
	{
		free_table(table);
		write(2, "sem_open failed\n", 17);
		return (NULL);
	}
	table->lunch_start = get_time_in_ms();
	return (table);
}

static t_philo	*init_philo(t_args *args, t_table *table, int id)
{
	t_philo	*philo ;

	philo = malloc(sizeof(t_philo));
	philo->args = args ;
	philo->table = table ;
	philo->id = id ;
	philo->nb_time_ate = 0 ;
	philo->last_meal = get_time_in_ms();
	return (philo);
}

t_philo	**create_philos(t_args *args, t_table *table)
{
	t_philo	**philos ;
	int		i ;

	philos = malloc(sizeof(t_philo *) * args->nb_philo);
	i = -1 ;
	while (++i < args->nb_philo)
	{
		philos[i] = init_philo(args, table, i + 1);
		if (!philos[i])
			return (free_philos(philos, i + 1), NULL);
	}
	return (philos);
}
