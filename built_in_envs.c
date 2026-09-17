/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_envs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:36:40 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 23:04:25 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	bin_unset(char **argv, t_env_map *envs)
{
	t_env	*u_env;

	if (!argv || !argv[0] || !argv[1] || (argv[1] && argv[2]))
	{
		write(STDERR_FILENO, "unset: arguments error\n", 23);
		return (1);
	}
	u_env = env_get(envs, argv[1]);
	if (!u_env)
	{
		write(STDERR_FILENO, "unset: no such variable\n", 24);
		return (1);
	}
	return (env_remove(envs, u_env->key_val[0].data));
}

int	bin_env(char **argv, t_env_map *envs)
{
	if (!argv || !argv[0] || argv[1])
	{
		write(STDERR_FILENO, "env: arguments error\n", 21);
		return (1);
	}
	print_map(envs);
	return (0);
}
