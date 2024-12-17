/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:44:24 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/17 12:20:27 by zabu-bak         ###   ########.fr       */
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
} t_data;

#endif
