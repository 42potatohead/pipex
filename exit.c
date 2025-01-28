/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:33:55 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/28 15:34:04 by zabu-bak         ###   ########.fr       */
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
