/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:57:29 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 05:23:05 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*get_expanded_var(char *arg, t_env_map *envs)
{
	t_env	*env_got;

	env_got = env_get(envs, arg);
	if (!env_got)
		return (NULL);
	return (cp_str_data(env_got->key_val[1].data));
}

static void	refine_arg(char **arg, int env_pos, t_env_map *envs)
{
	char	*arg_cp;
	char	*tmp;
	char	*env_cp;
	int		env_end_pos;
	char	t_val;

	env_end_pos = 1;
	while ((*arg)[env_pos + env_end_pos]
			&& (is_alpha((*arg)[env_pos + env_end_pos])
			|| (*arg)[env_pos + env_end_pos] == '?'))
		env_end_pos += 1;
	(*arg)[env_pos] = '\0';
	t_val = (*arg)[env_pos + env_end_pos];
	(*arg)[env_pos + env_end_pos] = '\0';
	arg_cp = cp_str_data(*arg);
	env_cp = get_expanded_var(&(*arg)[env_pos + 1], envs);
	(*arg)[env_pos + env_end_pos] = t_val;
	tmp = str_cat(arg_cp, env_cp).data;
	free_memo((void **)&arg_cp);
	arg_cp = str_cat(tmp, &(*arg)[env_pos + env_end_pos]).data;
	free_memo((void **)&tmp);
	free_memo((void **)&env_cp);
	(*arg)[env_pos] = '$';
	free_memo((void **)arg);
	(*arg) = arg_cp;
}

int	expand_args(char **argv, t_token_type *types, t_env_map *envs)
{
	size_t	c_arg;
	size_t	c_pos;

	if (!argv || !argv[0])
		return (1);
	c_arg = 1;
	while (argv && argv[c_arg])
	{
		c_pos = 0;
		while (argv[c_arg] && argv[c_arg][c_pos])
		{
			if (argv[c_arg][c_pos] == '$' && types[c_arg] != S_QUOTE)
			{
				refine_arg(&argv[c_arg], c_pos, envs);
				break ;
			}
			c_pos += 1;
		}
		c_arg += 1;
	}
	return (0);
}
