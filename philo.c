/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:05:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/13 03:59:48 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	serving_plates(t_args *args, t_table *table,
	t_philo **philos, pthread_t *threads)
{
	int	i ;

	i = -1 ;
	while (++i < args->nb_philo)
		if (pthread_create(threads + i, NULL, philosophing, philos[i]) != 0)
			return (error_pthread(table));
	if (pthread_create(threads + i++, NULL, monitoring, philos) != 0)
		error_pthread(table);
}

static void	waiting_till_they_finish(t_args *args, t_table *table,
	pthread_t *threads)
{
	int	i ;

	i = args->nb_philo + 1;
	while (--i >= 0)
		if (pthread_join(threads[i], NULL) != 0)
			return (error_pthread(table));
}

static void	bon_appetit(t_args *args, t_table *table)
{
	t_philo		**philos ;
	pthread_t	*threads ;

	philos = create_philos(args, table);
	if (!philos)
		return ;
	threads = malloc(sizeof(pthread_t) * (args->nb_philo + 1));
	pthread_mutex_lock(&table->mutex_update);
	serving_plates(args, table, philos, threads);
	if (table->state != PTHREAD_FAIL)
	{
		pthread_mutex_unlock(&table->mutex_update);
		waiting_till_they_finish(args, table, threads);
	}
	else
		pthread_mutex_unlock(&table->mutex_update);
	free(threads);
	free_philos(philos, args->nb_philo);
}

int	main(int argc, char *argv[])
{
	t_args	*args ;
	t_table	*table ;

	if (argc < 5 || argc > 6 || !parsing(argc, argv))
		return (error_args(), EXIT_FAILURE);
	args = init_args(argc, argv);
	table = init_table();
	if (!table)
		return (free(args), EXIT_FAILURE);
	bon_appetit(args, table);
	free(args);
	if (table->state == PTHREAD_FAIL)
		return (free_table(table), EXIT_FAILURE);
	free_table(table);
	return (EXIT_SUCCESS);
}
