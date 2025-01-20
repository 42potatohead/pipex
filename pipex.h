/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:44:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/20 21:32:12 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include "./printf/ft_printf.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

typedef struct s_data
{
	int fd;
	int fd2;
	char **cmd1;
	char **cmd2;
	int pipefd[2];
	int pid1;
	int pid2;
	int	ecmd1;
	int	ecmd2;
	int outfile;
	int infile;
} t_data;

void	cleanup(t_data *data, char **cmd1, char **cmd2, int flag);
void	check_file(t_data *data, int ac, char **av, int inorout);
void init_var(t_data *data);
void ft_wait(t_data *data);
void	ft_fork(t_data *data, char *infile, char *outfile);
// void	pid_check(t_data *data, int pid, char **cmd, int fd);

#endif
