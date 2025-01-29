/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:23 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/29 18:44:55 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_path(t_data *data)
{
	free(data->pcmd1);
	free(data->pcmd2);
}

void	init_var(t_data *data)
{
	data->split = 1;
	data->split1 = 1;
	data->pid1 = -2;
	data->pid2 = -2;
	data->infile = 0;
	data->outfile = 0;
	data->ecmd1 = 0;
	data->ecmd1 = 0;
}

void	ft_wait(t_data *data, char **av)
{
	if (data->ecmd1 == 0)
	{
		waitpid(data->pid1, &data->fd2, 0);
		if (WEXITSTATUS(data->fd2) == 2)
			ft_printf("command not found: %s\n", av[2]);
	}
	if (data->ecmd2 == 0)
	{
		waitpid(data->pid2, &data->fd, 0);
		if (WEXITSTATUS(data->fd) == 2)
			ft_printf("command not found: %s\n", av[3]);
	}
	if (data->ecmd1 == 0)
	{
		waitpid(data->pid1, &data->fd2, 0);
		if (WEXITSTATUS(data->fd2) == 13)
			ft_printf("permission denied: %s\n", av[2]);
	}
	if (data->ecmd2 == 0)
	{
		waitpid(data->pid2, &data->fd, 0);
		if (WEXITSTATUS(data->fd) == 13)
			ft_printf("permission denied: %s\n", av[3]);
	}
}

void	ft_fork(t_data *data, char *infile, char *outfile)
{
	if (data->ecmd1 != 1)
		data->fd = open(infile, O_RDONLY);
	if (data->ecmd1 != 1 && data->fd == -1)
		data->infile = 1;
	if (data->ecmd1 == 0 && data->fd != -1)
	{
		data->pid1 = fork();
		pid_check(data, data->pid1, data->cmd1);
		close(data->fd);
	}
	if (data->ecmd2 == 1)
	{
		data->outfile = 1;
		cleanup(data, data->cmd1, data->cmd2, 1);
	}
	data->fd2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd2 == -1)
		data->outfile = 1;
	if (data->ecmd2 == 0 && data->outfile != 1)
	{
		data->pid2 = fork();
		pid_check(data, data->pid2, data->cmd2);
		cleanup(data, data->cmd1, data->cmd2, 1);
	}
}
