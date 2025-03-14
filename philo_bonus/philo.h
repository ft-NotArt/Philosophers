/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:10:37 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/13 19:46:45 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

# define SEM_FORK		"philo_forks"
# define SEM_DEATH		"philo_death"
# define SEM_DISPLAY	"philo_display"

typedef struct s_args
{
	int	nb_philo ;
	int	time_to_die ;
	int	time_to_eat ;
	int	time_to_sleep ;
	int	nb_time_must_eat ;
}	t_args;

typedef struct s_table
{
	sem_t			*forks ;
	sem_t			*death ;
	sem_t			*display ;
	long			lunch_start ;
}	t_table;

typedef struct s_philo
{
	t_args			*args ;
	t_table			*table ;
	int				id ;
	int				nb_time_ate ;
	long			last_meal ;
}	t_philo;

void	philosophing(t_philo **philos, int index, t_table *table, t_args *args);
int		parsing(int argc, char *argv[]);
void	error_args(void);
void	error_fork(t_table *table);
void	error_pthread(t_table *table);
t_args	*init_args(int argc, char *argv[]);
t_table	*init_table(t_args *args);
t_philo	**create_philos(t_args *args, t_table *table);
void	display(t_philo *philo, t_table *table, char *msg);
void	miam_miam(t_philo *philo, t_table *table);
void	zzz_and_mmm(t_philo *philo, t_table *table);
void	free_table(t_table *table);
void	free_philos(t_philo **philosophers, int nb_philos);
void	free_all(t_philo **philos, t_table *table, t_args *args);
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
long	get_time_in_ms(void);
long	get_time_since(long time);
void	msleep(long ms);

#endif