/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:39:57 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:39:58 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

size_t	get_data_strlen(const char *str)
{
	size_t	res;

	res = 0;
	while (str && str[res])
		res += 1;
	return (res);
}

char	*cp_str_data(const char *ref_data)
{
	char	*res;
	size_t	ref_size;

	if (ref_data != NULL)
	{
		ref_size = get_data_strlen(ref_data);
		res = (char *)malloc((ref_size + 1) * sizeof(char));
		while (ref_size > 0)
		{
			res[ref_size] = ref_data[ref_size];
			ref_size -= 1;
		}
		res[0] = ref_data[0];
	}
	else
		res = NULL;
	return (res);
}

static char	*crt_str_data(const char *ref_data, size_t size)
{
	char	*res;
	size_t	c_pos;

	c_pos = 0;
	if (ref_data != NULL && size > 0)
	{
		res = (char *)malloc((size + 1) * sizeof(char));
		while (ref_data[c_pos] && c_pos < size)
		{
			res[c_pos] = ref_data[c_pos];
			c_pos += 1;
		}
		res[c_pos] = '\0';
	}
	else
		res = NULL;
	return (res);
}

t_string	create_string(const char *ref_data, size_t size)
{
	t_string	res;

	res.data = crt_str_data(ref_data, size);
	res.size = size;
	return (res);
}

void	init_str(t_string *str)
{
	str->data = NULL;
	str->size = 0;
}
