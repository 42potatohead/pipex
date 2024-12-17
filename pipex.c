/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:45:53 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/17 12:48:00 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int check_file(int ac, char **av, int inorout)
{
	if (ac != 5)
		return(ft_printf("Wrong number of arugments", 0));
	if (inorout == 0)
	{
		if(access(av[1], F_OK) != 0 || access(av[1], R_OK) != 0)
		{
			perror("Infile missing");
			exit(errno);
		}
	}
	else
	{
		if(access(av[4], F_OK) == 0)
			unlink(av[4]);
	}
	return (1);
}

int	child(int pid, char **cmd, int pipefd[], int fd, int inorout)
{
	if (pid == 0)
	{
		if (inorout == 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
			dup2(pipefd[1], STDOUT_FILENO);
		}
		else
		{
			// if outfile exists, unlink it and recreate it with permissions 0644
			dup2(fd, STDOUT_FILENO);
			dup2(pipefd[0], STDIN_FILENO);
			close(fd);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		if(execve(ft_strjoin("/bin/", cmd[0]), cmd, NULL) == -1)
			return(errno);
	}
	return (errno);
}

void cleanup(char **cmd1, char **cmd2)
{
	int i = 0;
	while (cmd1[i])
	{
		free(cmd1[i]);
		i++;
	}
	i = 0;
	while (cmd2[i])
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd1);
	free(cmd2);
}

void	pid_check(int pid, char **cmd1, char **cmd2)
{
	if (pid == -1)
	{
		perror("");
		cleanup(cmd1, cmd2);
		exit(errno);
	}
}

int	main(int ac, char **av)
{
	t_data data;

	check_file(ac, av, 0);
	data.fd = open(av[1], O_RDONLY);

	data.cmd1 = ft_split(av[2], ' ');
	data.cmd2 = ft_split(av[3], ' ');
	if (pipe(data.pipefd) == -1)
		perror("pipe error");
	data.pid1 = fork();
	pid_check(data.pid1, data.cmd1, data.cmd2);
	child(data.pid1, data.cmd1, data.pipefd, data.fd, 0);
	check_file(ac, av, 1);
	data.fd2 = open(av[4], O_RDWR | O_CREAT, 0644);
	data.pid2 = fork();
	pid_check(data.pid2, data.cmd1, data.cmd2);
	child(data.pid2,data.cmd2, data.pipefd, data.fd2, 1);

	close(data.pipefd[0]);
	close(data.pipefd[1]);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	cleanup(data.cmd1, data.cmd2);
	return (errno);
}
