/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:08:51 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 20:35:47 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	throw_args_error(void)
{
	write(STDERR_FILENO, "export: invalid argument\n", 25);
	return (1);
}

static int	throw_format_error(int err_code, char *key)
{
	if (err_code == 0)
		write(STDERR_FILENO, "export_invalid_format: expexted key=value\n", 42);
	else if (err_code == 1)
		write(STDERR_FILENO, "export_invalid_format: invalid key\n", 20);
	free_memo((void **)&key);
	return (1);
}

int	bin_export(char **argv, t_env_map *envs)
{
	char	*key;
	char	*val;
	char	*key_cp;
	int		res;

	if (!argv || !argv[0] || !argv[1] || (argv[1] && argv[2]))
		return (throw_args_error());
	key = cp_str_data(argv[1]);
	val = chr_in_str_pos('=', key);
	if (!val)
		return (throw_format_error(0, key));
	*val = '\0';
	val += 1;
	if (!is_alpha(key[0]) && key[0] != '_')
		return (throw_format_error(1, key));
	key_cp = key;
	while (key_cp && *key_cp)
	{
		if (!is_al_num(*key_cp) && *key_cp != '_')
			return (throw_format_error(0, key));
		key_cp += 1;
	}
	res = env_add(envs, key, val);
	free_memo((void **)&key);
	return (res);
}
