/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:38:16 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 01:45:35 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environmentals.h"

size_t	hash(const char *str)
{
	size_t	djb_hashcode;
	size_t	idx;

	idx = 0;
	djb_hashcode = 5381;
	while (str && str[idx])
	{
		djb_hashcode = ((djb_hashcode << 5) + djb_hashcode) + str[idx];
		idx += 1;
	}
	return (djb_hashcode);
}

int	init_map(t_env_map *map, size_t buckets)
{
	size_t		c_bucket;

	c_bucket = 0;
	map->buckets = buckets;
	map->data = (t_env **)malloc(map->buckets * sizeof(t_env *));
	while (c_bucket < map->buckets)
	{
		map->data[c_bucket] = NULL;
		c_bucket += 1;
	}
	env_add(map, "PWD", getenv("PWD"));
	env_add(map, "HOME", getenv("HOME"));
	env_add(map, "PATH", getenv("PATH"));
	env_add(map, "?", "0");
	return (1);
}

void	destroy_map(t_env_map *map)
{
	t_env	*entry;
	t_env	*tmp;
	size_t	c_bucket;

	c_bucket = 0;
	while (c_bucket < map->buckets)
	{
		entry = map->data[c_bucket];
		while (entry)
		{
			tmp = entry;
			entry = entry->next;
			destroy_str(&tmp->key_val[0]);
			destroy_str(&tmp->key_val[1]);
			free_memo((void **)&tmp);
		}
		c_bucket += 1;
	}
	free_memo((void **)&map->data);
	map->buckets = 0;
}

void	print_map(t_env_map *map)
{
	t_env	*current;
	size_t	c_bucket;

	c_bucket = 0;
	while (c_bucket < map->buckets)
	{
		current = map->data[c_bucket];
		while (current)
		{
			if (cmp_str_data(current->key_val[0].data, "?") != 0)
				printf("%s=%s\n", current->key_val[0].data,
					current->key_val[1].data);
			current = current->next;
		}
		c_bucket += 1;
	}
}
