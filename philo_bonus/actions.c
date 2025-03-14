/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 04:36:49 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/15 04:39:19 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(t_philo *philo, t_table *table, char *msg)
{
	sem_wait(table->update);
	if (table->death->__align == 1)
	{
		sem_wait(table->display);
		printf("%10ld %3d %s \n",
			get_time_since(table->lunch_start), philo->id, msg);
		sem_post(table->display);
	}
	sem_post(table->update);
}

void	miam_miam(t_philo *philo, t_table *table)
{
	if (sem_wait(table->forks) == 0)
	{
		display(philo, table, "has taken a fork");
		usleep(200);
		if (sem_wait(table->forks) == 0)
		{
			display(philo, table, "has taken a fork");
			display(philo, table, "is eating");
			msleep(philo->args->time_to_eat);
			sem_wait(table->update);
			philo->last_meal = get_time_in_ms();
			philo->nb_time_ate++ ;
			sem_post(table->update);
			sem_post(table->forks);
		}
		sem_post(table->forks);
	}
}

void	zzz_and_mmm(t_philo *philo, t_table *table)
{
	display(philo, table, "is sleeping");
	msleep(philo->args->time_to_sleep);
	display(philo, table, "is thinking");
}
