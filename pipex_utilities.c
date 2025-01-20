/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:10:23 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/20 21:31:10 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_var(t_data *data)
{
	data->pid1 = -2;
	data->pid2 = -2;
	data->infile = 0;
	data->outfile = 0;
	data->ecmd1 = 0;
	data->ecmd1 = 0;
}

void	ft_wait(t_data *data)
{
	if (data->ecmd1 == 0)
		waitpid(data->pid1, &data->fd2, 0);
	if (data->ecmd2 == 0)
		waitpid(data->pid2, &data->fd, 0);
}

// void	ft_fork(t_data *data, char *infile, char *outfile)
// {
// 	data->fd = open(infile, O_RDONLY);
// 	if (data->fd == -1)
// 		data->infile = 1;
// 	if (data->ecmd1 == 0 && data->fd != -1)
// 	{
// 		data->pid1 = fork();
// 		pid_check(data, data->pid1, data->cmd1, data->fd);
// 	}
// 	if (data->ecmd2 == 1)
// 	{
// 		data->outfile = 1;
// 		cleanup(data, data->cmd1, data->cmd2, 1);
// 	}
// 	data->fd2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (data->fd2 == -1)
// 		data->outfile = 1;
// 	if (data->ecmd2 == 0 && data->outfile != 1)
// 	{
// 		data->pid2 = fork();
// 		pid_check(data, data->pid2, data->cmd2, data->fd2);
// 		cleanup(data, data->cmd1, data->cmd2, 1);
// 	}
// }
