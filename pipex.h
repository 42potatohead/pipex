/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:44:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2025/01/29 18:42:35 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int		fd;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		ecmd1;
	int		ecmd2;
	int		outfile;
	int		infile;
	char	*pcmd1;
	char	*pcmd2;
	int		split;
	int		split1;
}			t_data;


void		check_arg(t_data *data, char **av);
void		exit_status(t_data *data);
void		close_path(t_data *data);
void		cleanup(t_data *data, char **cmd1, char **cmd2, int flag);
void		check_file(t_data *data, char **av, int inorout);
void		init_var(t_data *data);
void		ft_wait(t_data *data, char **av);
void		ft_fork(t_data *data, char *infile, char *outfile);
void		pid_check(t_data *data, int pid, char **cmd);

#endif
