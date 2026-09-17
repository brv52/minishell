/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:00:17 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:00:17 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

static int	dif_sign(char **str)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
		{
			*str += 1;
			return (-1);
		}
		else
		{
			*str += 1;
			return (1);
		}
	}
	return (1);
}

int	ft_isdigit(const char c)
{
	return (c >= '0' && c <= '9');
}

static void	trim_ws(char **str)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		*str += 1;
}

int	ft_atoi(char *nptr)
{
	char	*str;
	int		sign;
	int		res;

	res = 0;
	str = (char *)nptr;
	trim_ws(&str);
	sign = dif_sign(&str);
	while (ft_isdigit(*str))
	{
		res *= 10;
		res += *str - '0';
		str += 1;
	}
	return (res * sign);
}
