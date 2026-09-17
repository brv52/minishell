/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals_operators_0.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:49:55 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 03:53:31 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environmentals.h"

static int	throw_env_add_error(int err_code, t_string *val)
{
	if (err_code == 0)
		write(STDERR_FILENO, "env_add: invalid arguments\n", 27);
	else if (err_code == 1)
	{
		write(STDERR_FILENO, "env_add: environmental already exists\n", 38);
		destroy_str(val);
	}
	return (1);
}

int	env_add(t_env_map *map, const char *key, const char *val)
{
	size_t	key_idx;
	t_env	*current;
	t_env	*n_node;

	if (!key || !val || !map)
		throw_env_add_error(0, NULL);
	key_idx = hash(key) % map->buckets;
	current = map->data[key_idx];
	while (current)
	{
		if (cmp_str_data(current->key_val[0].data, key) == 0)
			return (env_update(map, key, val));
		if (!current->next)
			break ;
		current = current->next;
	}
	n_node = (t_env *)malloc(sizeof(t_env));
	n_node->key_val[0] = create_string(key, ft_strlen(key));
	n_node->key_val[1] = create_string(val, ft_strlen(val));
	n_node->next = NULL;
	if (current)
		current->next = n_node;
	else
		map->data[key_idx] = n_node;
	return (0);
}

t_env	*env_get(t_env_map *map, const char *key)
{
	t_env	*stored;

	stored = map->data[hash(key) % map->buckets];
	while (stored && cmp_str_data(stored->key_val[0].data, key) != 0)
		stored = stored->next;
	if (stored && cmp_str_data(stored->key_val[0].data, key) != 0)
		stored = NULL;
	if (!stored)
		return (NULL);
	return (stored);
}

int	env_remove(t_env_map *map, const char *key)
{
	t_env	*del_env;
	t_env	*prev;
	size_t	idx;

	idx = hash(key) % map->buckets;
	del_env = map->data[idx];
	prev = NULL;
	while (del_env)
	{
		if (cmp_str_data(del_env->key_val[0].data, key) == 0)
		{
			if (prev)
				prev->next = del_env->next;
			else
				map->data[idx] = map->data[idx]->next;
			destroy_str(&del_env->key_val[0]);
			destroy_str(&del_env->key_val[1]);
			free_memo((void **)&del_env);
			return (0);
		}
		prev = del_env;
		del_env = del_env->next;
	}
	return (1);
}
