/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:05:04 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/15 03:26:22 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	delete_semaphores(t_table *table)
{
	(sem_close(table->forks), sem_unlink(SEM_FORK));
	(sem_close(table->death), sem_unlink(SEM_DEATH));
	(sem_close(table->display), sem_unlink(SEM_DISPLAY));
	(sem_close(table->update), sem_unlink(SEM_UPDATE));
}

void	free_table(t_table *table)
{
	delete_semaphores(table);
	free(table);
}

void	free_philos(t_philo **philosophers, int nb_philos)
{
	while (nb_philos--)
		free(philosophers[nb_philos]);
	free(philosophers);
}

void	free_all(t_philo **philos, t_table *table, t_args *args)
{
	free_philos(philos, args->nb_philo);
	free_table(table);
	free(args);
}
