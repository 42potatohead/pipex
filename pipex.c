/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:45:53 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/20 17:47:10 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_file(t_data *data, int ac, char **av, int inorout)
{
	data->ecmd1 = 0;
	data->ecmd2 = 0;
	if (ac != 5)
		exit(-1);
	if (inorout == 0)
	{
		if (access(av[1], F_OK) != 0 || access(av[1], R_OK) != 0)
		{
			perror("Infile missing");
			exit(errno);
		}
		if (av[2][0])
			data->cmd1 = ft_split(av[2], ' ');
		else
			data->ecmd1 = 1;
		if (av[3][0])
			data->cmd2 = ft_split(av[3], ' ');
		else
			data->ecmd2 = 1;
	}
}

int	child(int pid, char **cmd, int pipefd[], int fd, int inorout, t_data *data)
{
	if (pid == 0)
	{
		if (inorout == 1)
			close(data->fd);
		if (inorout == 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			dup2(pipefd[1], STDOUT_FILENO);
		}
		else
		{
			dup2(fd, STDOUT_FILENO);
			dup2(pipefd[0], STDIN_FILENO);
			close(fd);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		if (execve(ft_strjoin("/bin/", cmd[0]), cmd, NULL) == -1)
			return (errno);
	}
	return (errno);
}

void	cleanup(t_data *data, char **cmd1, char **cmd2)
{
	int	i;

	i = 0;
	if (data->ecmd1 == 0)
	{
		while (cmd1[i])
		{
			free(cmd1[i]);
			i++;
		}
		free(cmd1);
	}
	i = 0;
	if (data->ecmd2 == 0)
	{
		while (cmd2[i])
		{
			free(cmd2[i]);
			i++;
		}
		free(cmd2);
	}
}
// find a way to utilitize this function correctly

void	pid_check(t_data *data, int pid, char **cmd1, char **cmd2)
{
	if (pid == -1)
	{
		perror("");
		cleanup(data, cmd1, cmd2);
		exit(errno);
	}
}
// shorten main

int	main(int ac, char **av)
{
	t_data	data;

	check_file(&data, ac, av, 0);
	data.fd = open(av[1], O_RDONLY);
	if (pipe(data.pipefd) == -1)
		perror("pipe error");
	if (data.ecmd1 == 0)
	{
		data.pid1 = fork();
		pid_check(&data, data.pid1, data.cmd1, data.cmd2);
		child(data.pid1, data.cmd1, data.pipefd, data.fd, 0, &data);
	}
	data.fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.ecmd2 == 0)
	{
		data.pid2 = fork();
		pid_check(&data, data.pid2, data.cmd1, data.cmd2);
		child(data.pid2, data.cmd2, data.pipefd, data.fd2, 1, &data);
	}
	close(data.pipefd[0]);
	close(data.pipefd[1]);
	close(data.fd);
	close(data.fd2);
	if (data.ecmd1 == 0)
		waitpid(-1, &data.fd, 0);
	if (data.ecmd2 == 0)
		waitpid(-1, &data.fd, 0);
	cleanup(&data, data.cmd1, data.cmd2);
	return (WEXITSTATUS(data.fd));
}
