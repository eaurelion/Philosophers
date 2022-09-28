/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaurelio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 22:32:21 by eaurelio          #+#    #+#             */
/*   Updated: 2022/01/30 22:32:22 by eaurelio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static int	ft_isspace(int c)
{
	return (c == '\n' || c == '\t' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

static int	ft_sign(int c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = ft_sign(str[i]);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (n > 2147483647 && sign > 0)
			return (-1);
		if (n > 2147483648 && sign < 0)
			return (-1);
		n = n * 10 + (str[i++] - '0');
	}
	return ((int)(sign * n));
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
