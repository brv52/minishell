/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_connector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:51:21 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 05:18:21 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	throw_conn_error(void)
{
	write(STDERR_FILENO, "execute_connector: pipe creation error\n", 39);
	return (1);
}

static int	get_ret_val(t_token_type type, int *status)
{
	if (type == PIPE)
		return (WEXITSTATUS(status[1]));
	else if (type == OR)
		return (!(WEXITSTATUS(status[0]) == 0 || WEXITSTATUS(status[1]) == 0));
	else if (type == AND)
		return (!(WEXITSTATUS(status[0]) == 0 && WEXITSTATUS(status[1]) == 0));
	return (1);
}

static void	exec_child(t_ast_node *pipe_node, t_env_map *envs,
						int *pipe_fd, int ch_id)
{
	if (ch_id == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast_tree(pipe_node->s_operator.left, envs));
	}
	else if (ch_id == 1)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(execute_ast_tree(pipe_node->s_operator.right, envs));
	}
}

int	exec_or(t_ast_node *pipe_node, t_env_map *envs)
{
	int		pipe_fd[2];
	pid_t	pid[2];
	int		status[2];

	if (pipe(pipe_fd) == -1)
		return (throw_conn_error());
	pid[0] = fork();
	if (pid[0] == 0)
		exec_child(pipe_node, envs, pipe_fd, 0);
	pid[1] = fork();
	if (pid[1] == 0)
		exec_child(pipe_node, envs, pipe_fd, 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, second_hand);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	signal(SIGINT, handle_signal);
	piping_sign(status, pipe_node);
	return (get_ret_val(pipe_node->s_operator.op_type, status));
}

int	exec_and(t_ast_node *pipe_node, t_env_map *envs)
{
	int		pipe_fd[2];
	pid_t	pid[2];
	int		status[2];

	if (pipe(pipe_fd) == -1)
		return (throw_conn_error());
	pid[0] = fork();
	if (pid[0] == 0)
		exec_child(pipe_node, envs, pipe_fd, 0);
	close(pipe_fd[1]);
	signal(SIGINT, second_hand);
	waitpid(pid[0], &status[0], 0);
	if (WEXITSTATUS(status[0]) != 0)
	{
		close (pipe_fd[0]);
		return (1);
	}
	pid[1] = fork();
	if (pid[1] == 0)
		exec_child(pipe_node, envs, pipe_fd, 1);
	close(pipe_fd[0]);
	waitpid(pid[1], &status[1], 0);
	signal(SIGINT, handle_signal);
	piping_sign(status, pipe_node);
	return (get_ret_val(pipe_node->s_operator.op_type, status));
}
