/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <eduhgb5198@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <sys/time.h>
# include <stdlib.h>

int				ft_is_digit(char c);
long long int	ft_now(void);
int				ft_atoi(const char *str);
int				ft_isint(const char *str);
int				ft_strlen(const char *str);

int				ft_str_is_int(const char *str);
void			ft_putstr(const char *str);
void			ft_putnbr(uint64_t n);

#endif