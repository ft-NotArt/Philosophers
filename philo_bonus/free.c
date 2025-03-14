/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 01:05:04 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/13 00:53:48 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->display);
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
