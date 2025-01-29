/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:45:53 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/29 19:37:55 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_file(t_data *data, char **av, int inorout)
{
	data->ecmd1 = 0;
	data->ecmd2 = 0;
	if ((access(av[4], F_OK) == 0 && access(av[4], W_OK) != 0))
	{
		data->ecmd2 = 1;
		perror(av[4]);
	}
	if (inorout == 0)
	{
		if (access(av[1], F_OK) != 0 || access(av[1], R_OK) != 0)
		{
			data->ecmd1 = 1;
			perror(av[1]);
		}
		if (av[2][0] && data->ecmd1 != 1 && data->split == 1)
			data->cmd1 = ft_split(av[2], ' ');
		else
			data->ecmd1 = 1;
		if (av[3][0] && data->ecmd2 != 1 && data->split1 == 1)
			data->cmd2 = ft_split(av[3], ' ');
		else
			data->ecmd2 = 1;
	}
}

void	child(char **cmd, char *pcmd, int inorout, t_data *data)
{
	if (inorout == 0)
	{
		dup2(data->fd, STDIN_FILENO);
		close(data->fd);
		dup2(data->pipefd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(data->fd2, STDOUT_FILENO);
		dup2(data->pipefd[0], STDIN_FILENO);
		close(data->fd2);
	}
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	if (execve(pcmd, cmd, NULL) == -1)
	{
		data->fd = errno;
		if(cmd[0] != NULL)
			close_path(data);
		cleanup(data, data->cmd1, data->cmd2, 1);
		exit(data->fd);
	}
}

void	cleanup(t_data *data, char **cmd1, char **cmd2, int flag)
{
	int	i;

	i = 0;
	if (data->ecmd1 == 0 && cmd1 != NULL && data->split == 1)
	{
		while (cmd1[i])
			free(cmd1[i++]);
		free(cmd1);
	}
	i = 0;
	if (data->ecmd2 == 0 && cmd2 != NULL && data->split == 1)
	{
		while (cmd2[i])
			free(cmd2[i++]);
		free(cmd2);
	}
	if (flag == 1)
	{
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
	if (data->infile == 0 && data->ecmd1 != 1)
		close(data->fd);
	if (data->outfile == 0)
		close(data->fd2);
}

void	pid_check(t_data *data, int pid, char **cmd)
{
	if(cmd[0] != NULL)
		data->pcmd1 = ft_strjoin("/bin/", cmd[0]);
	else if(cmd[0] != NULL)
		data->pcmd2 = ft_strjoin("/bin/", cmd[0]);
	if (pid == -1)
	{
		perror("");
		cleanup(data, data->cmd1, data->cmd2, 1);
		exit(errno);
	}
	if (pid == 0 && pid == data->pid1)
	{
		child(cmd, data->pcmd1, 0, data);
		close_path(data);
		cleanup(data, data->cmd1, data->cmd2, 1);
	}
	if (pid == 0 && pid == data->pid2)
		child(cmd, data->pcmd2, 1, data);
	if(cmd[0] != NULL)
		close_path(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_var(&data);
	if (ac != 5)
	{
		ft_printf("Wrong number of arguments, Must be 4.\n");
		exit(-1);
	}
	check_arg(&data, av);
	check_file(&data, av, 0);
	if (pipe(data.pipefd) == -1)
		perror("");
	data.fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.fd2 != -1 && data.fd2 != 0)
		close(data.fd2);
	ft_fork(&data, av[1], av[4]);
	if (data.ecmd2 != 0 && data.outfile == 1 && data.fd2 != -1 && data.fd2 != 0)
		close(data.fd2);
	ft_wait(&data, av);
	exit_status(&data);
}
