/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 07:50:38 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/15 04:42:11 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_fulfilled(t_philo *philo, t_table *table, t_args *args)
{
	bool	res ;

	sem_wait(table->update);
	res = philo->nb_time_ate == args->nb_time_must_eat ;
	sem_post(table->update);
	return (res);
}

static bool	check_dead(t_philo *philo, t_table *table, t_args *args)
{
	bool res ;

	sem_wait(table->update);
	res = get_time_since(philo->last_meal) > args->time_to_die ;
	sem_post(table->update);
	return (res);
}

static bool	meal_shall_continue(t_philo *philo, t_table *table, t_args *args)
{
	bool	res ;

	sem_wait(table->update);
	res = table->death->__align != 0 ;
	sem_post(table->update);
	res = res && !check_dead(philo, table, args)
			&& !check_fulfilled(philo, table, args);
	return (res);
}

static void	*mini_monitoring(void *param)
{
	t_philo	*philo ;
	t_table	*table ;
	t_args	*args ;

	philo = (t_philo *) param ;
	table = philo->table ;
	args = philo->args ;
	while (true)
	{
		if (check_dead(philo, table, args))
		{
			display(philo, table, "died \a");
			sem_wait(table->update);
			table->death->__align = 0 ;
			sem_post(table->update);
		}
		sem_wait(table->update);
		if (table->death->__align == 0)
			return(sem_post(table->update), NULL);
		sem_post(table->update);
		if (check_fulfilled(philo, table, args))
			return (NULL);
	}
	return (NULL);
}

void	philosophing(t_philo **philos, int index, t_table *table, t_args *args)
{
	t_philo		*philo ;
	pthread_t	thread ;

	philo = philos[index];
	thread = 0 ;
	if (pthread_create(&thread, NULL, mini_monitoring, philo) != 0)
		(error_pthread(table), free_all(philos, table, args), exit(1));
	if (args->nb_philo == 1)
	{
		(sem_wait(table->forks), display(philo, table, "has taken a fork"));
		(msleep(philo->args->time_to_die + 100), sem_post(table->forks));
	}
	if (philo->id % 2 == 0)
		msleep(philo->args->time_to_eat / 2);
	while (meal_shall_continue(philo, table, args))
	{
		miam_miam(philo, table);
		zzz_and_mmm(philo, table);
	}
	pthread_join(thread, NULL);
	free_all(philos, table, args);
	exit(0);
}
