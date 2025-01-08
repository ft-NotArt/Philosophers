/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:10:37 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/08 23:36:55 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_args
{
	int	nb_philo ;
	int	time_to_die ;
	int	time_to_eat ;
	int	time_to_sleep ;
	int	nb_time_must_eat ;
}	t_args ;

typedef struct s_table
{
	pthread_mutex_t mutex_dead ;
	bool			dead_philo ;
	pthread_mutex_t mutex_fullfilled ;
	int				nb_fullfilled_philos ;
}	t_table ;

typedef struct s_philo
{
	t_args			*args ;
	t_table			*table ;
	int				id ;
	pthread_mutex_t	right_fork ;
	pthread_mutex_t	*left_fork ;
	int				nb_time_ate ;
}	t_philo ;

int		parsing(int argc, char *argv[]);
void	error_args(void);
t_args	*init_args(int argc, char *argv[]);
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);

#endif