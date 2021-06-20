/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:38:10 by namerei           #+#    #+#             */
/*   Updated: 2020/11/19 15:44:30 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_isspace(int a)
{
	if (a == '\n' || a == '\v' || a == '\r'\
	|| a == '\t' || a == '\f' || a == ' ')
		return (1);
	return (0);
}

static int	ft_check_if_not_digit_have(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long	i;
	unsigned long	n;
	int				sign;

	i = 0;
	n = 0;
	sign = 1;
	if (!ft_check_if_not_digit_have((char *)str))
		return (-1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		n = 10 * n + (str[i] - '0');
		i++;
	}
	return ((int)sign * (int)n);
}
