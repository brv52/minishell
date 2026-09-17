/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentals.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:49:04 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 01:50:02 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENTALS_H
# define ENVIRONMENTALS_H

# include "utilities.h"

typedef struct environmental
{
	t_string				key_val[2];
	struct environmental	*next;
}	t_env;

typedef struct env_map
{
	t_env	**data;
	size_t	buckets;
}	t_env_map;

size_t	hash(const char *str);
int		init_map(t_env_map *map, size_t buckets);
int		env_add(t_env_map *map, const char *key, const char *val);
t_env	*env_get(t_env_map *map, const char *key);
int		env_remove(t_env_map *map, const char *key);
void	destroy_map(t_env_map *map);
void	print_map(t_env_map *map);
int		env_get_status(t_env_map *map);
int		env_update(t_env_map *map, const char *key, const char *val);

#endif
