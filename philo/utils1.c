/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <eduhgb5198@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

long long int
	ft_now(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str++ <= '9')
		ret = *(str - 1) - 48 + 10 * ret;
	return (ret * sign);
}

int	ft_str_is_int(const char *str)
{
	const char	*cmp;
	int			len;
	int			cmp_len;
	int			i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		cmp = "-2147483648";
	else
		cmp = "2147483647";
	cmp_len = ft_strlen(cmp);
	len = ft_strlen(str);
	if (len < cmp_len)
		return (1);
	if (len > cmp_len)
		return (0);
	while (i < len)
	{
		if (str[i] > cmp[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
