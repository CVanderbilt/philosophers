/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <eduhgb5198@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by eherrero          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>
#include <unistd.h>

int	ft_skip_char(const char *str, int i, char c)
{
	while (str[i] == c)
		i++;
	return (i);
}

static int	max_check(const char *str, int i, int len, int neg)
{
	const char	*max;
	int			j;

	max = "2147483647";
	if (neg)
		max = "2147483648";
	if (len < 10)
		return (1);
	if (len > 10)
		return (0);
	j = -1;
	while (max[++j])
		if (max[j] < str[i++])
			return (0);
	return (1);
}

int	ft_strisint(const char *str)
{
	int	i;
	int	neg;

	neg = 0;
	i = ft_skip_char(str, 0, ' ');
	if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	if (!ft_is_digit(str[i]))
		return (0);
	ft_skip_char(str, i, '0');
	if (!max_check(str, i, ft_strlen(str + i), neg))
		return (0);
	while (ft_is_digit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	ft_putstr(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, str + i, 1);
}

void	ft_putnbr(uint64_t n)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(1, &str[length--], 1);
}
