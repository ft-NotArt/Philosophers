/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 04:36:49 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/12 09:19:11 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_if_no_dead(t_philo *philo, char *msg)
{
	if (meal_shall_continue(philo->table))
	{
		pthread_mutex_lock(&philo->table->mutex_display);
		printf("%10ld %3d %s \n",
			get_time_launch(philo->table), philo->id, msg);
		pthread_mutex_unlock(&philo->table->mutex_display);
	}
}

void	miam_miam(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	display_if_no_dead(philo, "has taken a fork");
	if (philo->left_fork == NULL)
		msleep(philo->args->time_to_die + 100);
	else
	{
		pthread_mutex_lock(philo->left_fork);
		display_if_no_dead(philo, "has taken a fork");
		display_if_no_dead(philo, "is eating");
		msleep(philo->args->time_to_eat);
		pthread_mutex_lock(&philo->table->mutex_update);
		philo->last_meal = get_time_in_ms();
		philo->nb_time_ate++ ;
		pthread_mutex_unlock(&philo->table->mutex_update);
		pthread_mutex_unlock(philo->left_fork);
	}
	pthread_mutex_unlock(&philo->right_fork);
}

void	zzzzz_and_mmmmm(t_philo *philo)
{
	display_if_no_dead(philo, "is sleeping");
	msleep(philo->args->time_to_sleep);
	display_if_no_dead(philo, "is thinking");
}
