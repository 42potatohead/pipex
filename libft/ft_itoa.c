/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:30:18 by zabu-bak          #+#    #+#             */
/*   Updated: 2024/09/03 01:17:21 by zabu-bak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, int n, int sign, int len)
{
	int	i;
	int	digit;

	i = len - 1;
	while (i >= 0)
	{
		digit = sign * (n % 10);
		if (digit >= 0)
		{
			str[i] = digit + '0';
		}
		else
		{
			str[i] = -digit + '0';
		}
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = get_num_len(n);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	fill_str(str, n, sign, len);
	if (sign == -1)
	{
		str[0] = '-';
	}
	return (str);
}
