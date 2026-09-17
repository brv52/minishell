/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:39:59 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:40:34 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	destroy_str(t_string *str)
{
	free_memo((void **)&str->data);
	str->size = 0;
}

int	cmp_str_data(const char *ref, const char *cmp_to)
{
	size_t	c_pos;

	c_pos = 0;
	while ((ref && cmp_to)
		&& (ref[c_pos] && cmp_to[c_pos]))
	{
		if (ref[c_pos] != cmp_to[c_pos])
			return (ref[c_pos] - cmp_to[c_pos]);
		c_pos += 1;
	}
	if (ref[c_pos] != cmp_to[c_pos])
		return (ref[c_pos] - cmp_to[c_pos]);
	return (0);
}

int	str_chr(char c, const char *str)
{
	int	res;

	res = 0;
	while (str && str[res])
	{
		if (str[res] == c)
			return (res);
		res += 1;
	}
	return (-1);
}

char	*chr_in_str_pos(char c, char *str)
{
	int	c_pos;

	c_pos = str_chr(c, str);
	if (c_pos == -1)
		return (NULL);
	return (&str[c_pos]);
}
