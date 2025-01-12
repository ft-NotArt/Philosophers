/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 07:50:38 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/12 09:23:17 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	meal_shall_continue(t_table *table)
{
	bool	res ;

	pthread_mutex_lock(&table->mutex_update);
	res = (table->state == ENJOY_YOUR_MEAL);
	pthread_mutex_unlock(&table->mutex_update);
	return (res);
}

void	*philosophing(void *param)
{
	t_philo	*philo ;

	philo = (t_philo *) param ;
	if (philo->id % 2 == 0)
		msleep(philo->args->time_to_eat / 2);
	while (meal_shall_continue(philo->table))
	{
		miam_miam(philo);
		zzzzz_and_mmmmm(philo);
	}
	return (NULL);
}

static void	check_fullfilled(t_philo *philo, t_table *table, t_args *args)
{
	pthread_mutex_lock(&table->mutex_update);
	if (philo->nb_time_ate >= args->nb_time_must_eat)
		table->nb_fullfilled_philos++ ;
	if (args->nb_time_must_eat >= 0
		&& table->nb_fullfilled_philos >= args->nb_philo)
		table->state = THEY_ATE_SO_MUCH ;
	pthread_mutex_unlock(&table->mutex_update);
}

static void	check_dead(t_philo *philo, t_table *table, t_args *args)
{
	pthread_mutex_lock(&table->mutex_update);
	if ((get_time_in_ms() - philo->last_meal) > args->time_to_die)
	{
		pthread_mutex_lock(&philo->table->mutex_display);
		printf("%10ld %3d died \n", get_time_launch(table), philo->id);
		pthread_mutex_unlock(&philo->table->mutex_display);
		table->state = WONT_THINK_NO_MORE ;
	}
	pthread_mutex_unlock(&table->mutex_update);
}

void	*monitoring(void *param)
{
	t_philo	**philos ;
	t_table	*table ;
	t_args	*args ;
	int		i ;

	philos = (t_philo **) param ;
	table = philos[0]->table ;
	args = philos[0]->args ;
	while (meal_shall_continue(table))
	{
		i = -1 ;
		while (++i < args->nb_philo && meal_shall_continue(table))
		{
			check_fullfilled(philos[i], table, args);
			check_dead(philos[i], table, args);
		}
	}
	return (NULL);
}
