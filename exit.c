/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:33:55 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/31 16:07:59 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_dup(t_data *data)
{
	if (data->dupm1 == 1)
	{
		free(data->cmd1[0]);
		free(data->cmd1);
	}
	if (data->dupm2 == 1)
	{
		free(data->cmd2[0]);
		free(data->cmd2);
	}
}

void	join_path(t_data *data, char **cmd)
{
	if (data->pcmd1 != NULL)
		free (data->pcmd1);
	if (cmd[0] != NULL)
		data->pcmd1 = ft_strjoin("/bin/", cmd[0]);
	else
		data->pcmd1 = ft_strjoin("/bin/", " ");
}

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
	exit (1);
}
