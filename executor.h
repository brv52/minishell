/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:48:40 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 04:10:28 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "environmentals.h"
# include "built_in.h"
# include "expander.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "signal_handler.h"
# include <fcntl.h>

int	execute_ast_tree(t_ast_node *node, t_env_map *envs);
int	exec_command(t_ast_node *op_node, t_env_map *envs);
int	is_bin(t_ast_node *node);
int	exec_bin(t_ast_node *node, t_env_map *envs, int bin_id);
int	throw_exec_error(int err_code);
int	throw_redir_error(int err_code, int s_stdin, int s_stdout);
int	reset_std(int saved_stdin, int saved_stdout);
int	exec_redir(t_ast_node *redir_node, t_env_map *envs);
int	exec_or(t_ast_node *pipe_node, t_env_map *envs);
int	exec_and(t_ast_node *pipe_node, t_env_map *envs);

#endif
