/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:33:55 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/29 18:42:48 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_status(t_data *data)
{
	if (data->ecmd2 == 0)
	{
		if (WEXITSTATUS(data->fd) == 2)
			exit(127);
		if (WEXITSTATUS(data->fd) == 13)
			exit(126);
		exit (WEXITSTATUS(data->fd));
	}
	exit (EXIT_FAILURE);
}

void	check_arg(t_data *data, char **av)
{
	int i;

	i = 0;
	while(av[2][i] && av[2][i] == ' ')
		i++;
	if (av[2][i] == '\0')
		data->split = 0;
	i = 0;
	while(av[3][i] && av[3][i] == ' ')
		i++;
	if (av[3][i] == '\0')
		data->split1 = 0;
}
