/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:21:35 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/08 19:00:53 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_check(char s, va_list *args, int *len)
{
	if (s == 's')
		ft_string(va_arg(*args, char *), len);
	else if (s == 'd' || s == 'i')
		ft_number(va_arg(*args, int), len);
	else if (s == 'p')
		ft_pointer(va_arg(*args, unsigned long), len);
	else if (s == 'x')
		ft_hex(va_arg(*args, unsigned int), len, 'x');
	else if (s == 'X')
		ft_hex(va_arg(*args, unsigned int), len, 'X');
	else if (s == '%')
		ft_string("%", len);
	else if (s == 'u')
		ft_unsing(va_arg(*args, unsigned int), len);
	else if (s == 'c')
		ft_c(va_arg(*args, int), len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			printf_check(str[i], &args, &len);
			i++;
		}
		else
		{
			ft_putstrlen(str[i]);
			i++;
			(len)++;
		}
	}
	va_end(args);
	return (len);
}
