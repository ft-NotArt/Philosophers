/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:10:37 by anoteris          #+#    #+#             */
/*   Updated: 2025/03/12 17:04:31 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_args
{
	int	nb_philo ;
	int	time_to_die ;
	int	time_to_eat ;
	int	time_to_sleep ;
	int	nb_time_must_eat ;
}	t_args;

typedef enum table_state
{
	ENJOY_YOUR_MEAL,
	WONT_THINK_NO_MORE,
	THEY_ATE_SO_MUCH,
	PTHREAD_FAIL
}	t_state;

typedef struct s_table
{
	pthread_mutex_t	mutex_update ;
	pthread_mutex_t	mutex_display ;
	t_state			state ;
	bool			*fullfilled_philos ;
	long			lunch_start ;
}	t_table;

typedef struct s_philo
{
	t_args			*args ;
	t_table			*table ;
	int				id ;
	pthread_mutex_t	right_fork ;
	pthread_mutex_t	*left_fork ;
	int				nb_time_ate ;
	long			last_meal ;
}	t_philo;

void	*philosophing(void *param);
void	*monitoring(void *param);
int		parsing(int argc, char *argv[]);
void	error_args(void);
void	error_pthread(t_table *table);
t_args	*init_args(int argc, char *argv[]);
t_table	*init_table(t_args *args);
t_philo	*init_philo(t_args *args, t_table *table, int id,
			pthread_mutex_t *left_fork);
t_philo	**create_philos(t_args *args, t_table *table);
bool	meal_shall_continue(t_table *table);
void	display_if_no_dead(t_philo *philo, char *msg);
void	miam_miam(t_philo *philo);
void	zzzzz_and_mmmmm(t_philo *philo);
void	free_table(t_table *table);
void	free_philo(t_philo *philo);
void	free_philos(t_philo **philosophers, int nb_philos);
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
long	get_time_in_ms(void);
long	get_time_launch(t_table *table);
void	msleep(long ms);

#endif