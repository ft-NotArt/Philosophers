/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:05:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/09 07:44:52 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophing(void *arg)
{
	t_philo	*philo ;

	philo = (t_philo *) arg ;

	printf("Philo : id=%d\n", philo->id);

	return (NULL);
}

// TODO: On failure, think to free table and args,
// -DONE-(as well as every other previous philo)
t_philo	**create_philos(t_args *args, t_table *table)
{
	t_philo	**philos ;
	int 	i ;

	philos = malloc(sizeof(t_philo *) * args->nb_philo);
	philos[0] = init_philo(args, table, 1, NULL);
	if (!philos[0])
		return (free_philos(philos, 1), NULL);
	i = 0 ;
	while (++i <= args->nb_philo)
	{
		philos[i] = init_philo(args, table, i + 1,
			&philos[i - 1]->right_fork);
		if (!philos[i])
			return (free_philos(philos, i + 1), NULL);
	}
	philos[0]->left_fork = &philos[i - 1]->right_fork ;
	return (philos);
}

void	bon_appetit(t_args *args, t_table *table)
{
	t_philo		**philos ;
	pthread_t	*threads ;
	int	i ;

	philos = create_philos(args, table);
	if (!philos)
	{
		free(args);
		free_table(table);
		return ;
	}
	threads = malloc(sizeof(pthread_t) * args->nb_philo);
	i = -1 ;
	while (++i < args->nb_philo)
	{
		if (pthread_create(threads + i, NULL, philosophing, philos[i]) != 0)
		{
			error_pthread(table);
			break ;
		}
	}
	while (--i >= 0)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			error_pthread(table);
			break ;
		}
	}
	free(threads);
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
		return (EXIT_FAILURE);
	
	printf("faut penser la \n");

	pthread_t thread1 ;
	t_philo	*philo1 ;

	philo1 = init_philo(args, table, 1, NULL);

	pthread_create(&thread1, NULL, philosophing, philo1);

	pthread_t thread2 ;
	t_philo	*philo2 ;

	philo2 = init_philo(args, table, 2, &philo1->right_fork);
	philo1->left_fork = &philo2->right_fork ;

	pthread_create(&thread2, NULL, philosophing, philo2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	free(args);
	return (EXIT_SUCCESS);	
}
