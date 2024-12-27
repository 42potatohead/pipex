/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:59:46 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/12/27 19:59:57 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(size_t num, int *len, char x)
{
	char	string[25];
	char	*base;
	int		i;

	i = 0;
	if (x == 'x')
		base = "0123456789abcdef";
	if (x == 'X')
		base = "0123456789ABCDEF";
	if (num == 0)
	{
		ft_string("0", len);
		return ;
	}
	while (num != 0)
	{
		string[i] = base[num % 16];
		num = num / 16;
		i++;
	}
	while (i--)
	{
		ft_putstrlen(string[i]);
		(*len)++;
	}
}

void	ft_number(int num, int *len)
{
	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	if (num < 0)
	{
		(*len)++;
		ft_putstrlen('-');
		num = -num;
	}
	if (num > 9)
		ft_number(num / 10, len);
	(*len)++;
	ft_putstrlen(num % 10 + '0');
}
