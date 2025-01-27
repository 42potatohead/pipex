/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:21:56 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/11/29 15:45:26 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_string(char *args, int *len);
void	printf_ft_putchar(char c);
void	ft_putstrlen(char args);
void	ft_number(int num, int *len);
void	ft_pointer(size_t ptr, int *len);
void	ft_hex(size_t num, int *len, char x);
void	ft_unsing(unsigned int num, int *len);
void	ft_c(char args, int *len);

#endif
