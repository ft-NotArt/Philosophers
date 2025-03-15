/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:05:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/15 02:51:00 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	serving_plates(t_args *args, t_table *table,
	t_philo **philos, pid_t *pids)
{
	int	i ;

	i = -1 ;
	while (++i < args->nb_philo)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			error_fork(table);
			if (table->death->__align != 0)
				sem_wait(table->death);
			return (EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			free(pids);
			philosophing(philos, i, table, args);
		}
		usleep(2);
	}
	return (EXIT_SUCCESS);
}

static void	waiting_til_they_finish(t_args *args, pid_t *pids)
{
	int	i ;

	i = -1 ;
	while (++i < args->nb_philo)
		if (pids[i] != -1)
			waitpid(pids[i], NULL, 0);
}

static bool	bon_appetit(t_args *args, t_table *table)
{
	t_philo	**philos ;
	pid_t	*pids ;
	bool	status ;

	philos = create_philos(args, table);
	if (!philos)
		return (EXIT_FAILURE);
	pids = malloc((args->nb_philo + 1) * sizeof(pid_t));
	memset(pids, -1, (args->nb_philo + 1) * sizeof(pid_t));
	status = serving_plates(args, table, philos, pids);
	waiting_til_they_finish(args, pids);
	free(pids);
	free_philos(philos, args->nb_philo);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_args	*args ;
	t_table	*table ;
	bool	status ;

	if (argc < 5 || argc > 6 || !parsing(argc, argv))
		return (error_args(), EXIT_FAILURE);
	args = init_args(argc, argv);
	table = init_table(args);
	if (!table)
		return (free(args), EXIT_FAILURE);
	status = bon_appetit(args, table);
	free(args);
	free_table(table);
	(sem_unlink(SEM_FORK), sem_unlink(SEM_DISPLAY), sem_unlink(SEM_DEATH));
	return (status);
}
