/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:07:45 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 05:19:37 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./minishell_debug/debug_minishell.h"

sig_atomic_t	g_signal;

static void	free_shell_data(t_shell_data *sh_data)
{
	destroy_str(&sh_data->u_promt);
	destroy_map(&sh_data->envs);
	rl_clear_history();
}

static void	data_cleanup(t_shell_data *sh_data)
{
	destroy_tokens(sh_data->tokens);
	destroy_ast_tree(sh_data->ast_tree);
	destroy_str(&sh_data->u_promt);
}

static int	execute_iteration(t_shell_data *sh_data)
{
	sh_data->tokens = tokenize(&sh_data->u_promt);
	if (!sh_data->tokens)
	{
		env_update(&sh_data->envs, "?", "1");
		return (1);
	}
	sh_data->ast_tree = parse_tokens(sh_data->tokens);
	if (!sh_data->ast_tree)
	{
		destroy_tokens(sh_data->tokens);
		env_update(&sh_data->envs, "?", "1");
		return (1);
	}
	if (execute_ast_tree(sh_data->ast_tree, &sh_data->envs) != 0)
	{
		env_update(&sh_data->envs, "?", "1");
		data_cleanup(sh_data);
		return (1);
	}
	data_cleanup(sh_data);
	return (0);
}

static void	shell_loop(t_shell_data *sh_data)
{
	while (1)
	{
		read_input(&sh_data->u_promt, env_get_status(&sh_data->envs));
		if (!sh_data->u_promt.data)
			break ;
		if (sh_data->u_promt.data[0] == '\0')
			continue ;
		if (execute_iteration(sh_data) != 0)
			continue ;
		env_update(&sh_data->envs, "?", "0");
	}
}

int	main(void)
{
	t_shell_data	sh_data;

	init_map(&sh_data.envs, 64);
	sig_init();
	sh_data.u_promt.data = NULL;
	shell_loop(&sh_data);
	free_shell_data(&sh_data);
	return (0);
}
