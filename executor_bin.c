/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:02:44 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 23:09:01 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_bin(t_ast_node *node)
{
	if (cmp_str_data(node->s_command.argv[0], "echo") == 0)
		return (1);
	else if (cmp_str_data(node->s_command.argv[0], "cd") == 0)
		return (2);
	else if (cmp_str_data(node->s_command.argv[0], "pwd") == 0)
		return (3);
	else if (cmp_str_data(node->s_command.argv[0], "export") == 0)
		return (4);
	else if (cmp_str_data(node->s_command.argv[0], "unset") == 0)
		return (5);
	else if (cmp_str_data(node->s_command.argv[0], "env") == 0)
		return (6);
	else if (cmp_str_data(node->s_command.argv[0], "exit") == 0)
		return (7);
	return (0);
}

int	exec_bin(t_ast_node *node, t_env_map *envs, int bin_id)
{
	if (bin_id == 1)
		return (bin_echo(node->s_command.argv, envs));
	else if (bin_id == 2)
		return (bin_cd(node->s_command.argv, envs));
	else if (bin_id == 3)
		return (bin_pwd(envs));
	else if (bin_id == 4)
		return (bin_export(node->s_command.argv, envs));
	else if (bin_id == 5)
		return (bin_unset(node->s_command.argv, envs));
	else if (bin_id == 6)
		return (bin_env(node->s_command.argv, envs));
	else if (bin_id == 7)
		return (bin_exit(node->s_command.argv));
	return (0);
}
