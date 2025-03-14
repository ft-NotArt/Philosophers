/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 07:50:38 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/14 22:43:40 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_fulfilled(t_philo *philo, t_args *args)
{
	if (philo->nb_time_ate == args->nb_time_must_eat)
		return (true);
	return (false);
}

static bool	check_dead(t_philo *philo, t_args *args)
{
	if (get_time_since(philo->last_meal) > args->time_to_die)
		return (true);
	return (false);
}

static bool	meal_shall_continue(t_philo *philo, t_table *table, t_args *args)
{
	return (table->death->__align != 0
		&& !check_dead(philo, args)
		&& !check_fulfilled(philo, args));
}

static void	*mini_monitoring(void *param)
{
	t_philo	*philo ;
	t_table	*table ;
	t_args	*args ;

	philo = (t_philo *) param ;
	table = philo->table ;
	args = philo->args ;
	while (meal_shall_continue(philo, table, args))
	{
		if (check_dead(philo, args))
		{
			display(philo, table, "died \a");
			if (table->death->__align != 0)
				sem_wait(table->death);
		}
	}
	return (NULL);
}

void	philosophing(t_philo **philos, int index, t_table *table, t_args *args)
{
	t_philo		*philo ;
	pthread_t	thread ;
	short		status ;

	philo = philos[index];
	thread = 0 ;
	if (philo->id % 2 == 0)
		msleep(philo->args->time_to_eat / 2);
	if (args->nb_philo == 1)
	{
		(sem_wait(table->forks), display(philo, table, "has taken a fork"));
		(msleep(philo->args->time_to_die + 5), sem_post(table->forks));
	}
	else
	{
		if (pthread_create(&thread, NULL, mini_monitoring, philo) != 0)
		{
			(error_pthread(table), free_all(philos, table, args));
			exit(EXIT_FAILURE);
		}
		while (meal_shall_continue(philo, table, args))
			(miam_miam(philo, table), zzz_and_mmm(philo, table));
	}
	status = meal_shall_continue(philo, table, args);
	(pthread_join(thread, NULL), free_all(philos, table, args), exit(status));
}
