/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 10:45:53 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/17 08:51:42 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <errno.h>

int	main(int ac, char **av)
{
	if (ac == 100)
		return 0;
	int pipefd[2];
	// fd 0 -- read stdin
	// fd 1 -- write stdout
	char **cmd1;
	char **cmd2;

	// splitting the input arguments into words ps. make it dynamic so it can accomedate more than 2 commands
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');

	int pid1;
	int pid2;
	if (pipe(pipefd) == -1)
		perror("pipe error");
	// fork creates a secondery process aka child process which is seperate from the main aka parent, ps. figure out how to dynamiclly create multiple forks.
	pid1 = fork();
	if (pid1 == -1)
		perror("fork error");
	/*
		child process #1
		Checks if the infile exists and has read permissions, Opens it, dupes its pointer to STDIN
		so that execve process can process it as cmd input, then it dupes the pointer of pipfd[1]
		which is stdout so that whatever the outcome of execve is processed as STDIN for the child process #2
	*/
	if (pid1 == 0)
	{
		// child process #1
		if(access(av[1], F_OK) != 0 || access(av[1], R_OK) != 0)
		{
			perror("wow");
			exit(0);
		}
		int fd = open(av[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if(execve(ft_strjoin("/bin/", cmd1[0]), cmd1, NULL) == -1)
			perror("wow");
	}
	pid2 = fork();
	if (pid2 == -1)
		perror("fork error");
	if (pid2 == 0)
	{
		// child process #2
		// char *arg[] = {"grep", "w", NULL};
		// if(access(av[4], F_OK) != 0 || access(av[4], R_OK) != 0)
		// {
		// 	perror("wow");
		// 	exit(0);
		// }
		int fd2 = open(av[4], O_RDWR | O_CREAT, 0644);
		dup2(fd2, STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		close(fd2);
		close(pipefd[0]);
		close(pipefd[1]);
		if(execve(ft_strjoin("/bin/", cmd2[0]), cmd2, NULL) == -1)
			perror("wow");
	}

	// cleanup
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	int i = 0;
	while (cmd1[i])
	{
		free(cmd1[i]);
		i++;
	}
	while (cmd2[i])
	{
		free(cmd2[i]);
		i++;
	}
	free(cmd1);
	free(cmd2);
	return errno;
}
