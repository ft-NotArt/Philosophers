/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:05:31 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/09 00:05:27 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_args	*args ;

	if (argc < 5 || argc > 6 || !parsing(argc, argv))
		return (error_args(), EXIT_FAILURE);
	args = init_args(argc, argv);

	
	printf("faut penser la \n");
	
	free(args);
	return (EXIT_SUCCESS);	
}