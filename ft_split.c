/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 02:32:10 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 02:32:22 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

static int	count_strings(char const *s, char c)
{
	size_t	res;
	int		in_word;

	in_word = 0;
	res = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			res += 1;
		}
		else if (*s == c)
			in_word = 0;
		s += 1;
	}
	return (res);
}

static char	*ft_slash_term(char const *src, size_t len)
{
	char	*buffer;
	size_t	pos;

	pos = 0;
	buffer = malloc((len + 2) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (src[pos] && pos < len)
	{
		buffer[pos] = src[pos];
		pos += 1;
	}
	buffer[len] = '/';
	buffer[len + 1] = '\0';
	return (buffer);
}

static void	skip(char const **s, char c, size_t *w_len)
{
	while (**s && **s == c)
		*s += 1;
	while (**s && **s != c)
	{
		*s += 1;
		*w_len += 1;
	}
}

char	**ft_slash_split(char const *s, char c)
{
	char	**set;
	size_t	w_len;
	size_t	w_current;

	if (!s)
		return (NULL);
	set = malloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!set)
		return (NULL);
	w_len = 0;
	w_current = 0;
	while (*s)
	{
		skip(&s, c, &w_len);
		if (w_len > 0)
		{
			set[w_current++] = ft_slash_term((s - w_len), w_len);
			w_len = 0;
		}
	}
	set[w_current] = NULL;
	return (set);
}
