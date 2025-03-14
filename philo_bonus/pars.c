/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 03:50:18 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/08 23:43:12 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pars_only_positive_numbers(int argc, char *argv[])
{
	int	i ;
	int	j ;

	i = 1 ;
	while (i < argc)
	{
		j = 0 ;
		if (argv[i][j] == '+')
			j++ ;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++ ;
		}
		i++ ;
	}
	return (1);
}

static bool	is_int_len(char *nbr)
{
	int	size ;
	int	i ;

	size = 0 ;
	i = 0 ;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		size++ ;
		i++ ;
	}
	while (nbr[i] == '0')
		i++ ;
	while (ft_isdigit(nbr[i]))
	{
		size++ ;
		i++ ;
	}
	return (size <= 11);
}

static int	pars_only_non_nul_int(int argc, char *argv[])
{
	long	value ;
	int		i ;

	i = 1 ;
	while (i < argc)
	{
		if (!is_int_len(argv[i]))
			return (0);
		value = ft_atol(argv[i]);
		if (value == 0 || value > INT_MAX)
			return (0);
		i++ ;
	}
	return (1);
}

int	parsing(int argc, char *argv[])
{
	return (pars_only_positive_numbers(argc, argv)
		&& pars_only_non_nul_int(argc, argv));
}
