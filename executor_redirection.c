/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:33:48 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 05:18:47 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_redir_in(t_ast_node *redir_node, int s_stdin, int s_stdout)
{
	int	fd;

	fd = open(redir_node->s_operator.right->s_command.argv[0], O_RDONLY);
	if (fd < 0)
		return (throw_redir_error(1, s_stdin, s_stdout));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_out(t_ast_node *redir_node, int s_stdin, int s_stdout)
{
	int	fd;

	fd = open(redir_node->s_operator.right->s_command.argv[0],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (throw_redir_error(2, s_stdin, s_stdout));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_append(t_ast_node *redir_node,
								int s_stdin, int s_stdout)
{
	int	fd;

	fd = open(redir_node->s_operator.right->s_command.argv[0],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (throw_redir_error(3, s_stdin, s_stdout));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_heredoc(t_ast_node *redir_node,
								int s_stdin, int s_stdout)
{
	char	*u_input;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (throw_redir_error(4, s_stdin, s_stdout));
	while (1)
	{
		u_input = readline("> ");
		if (!u_input)
			break ;
		if (cmp_str_data(u_input,
				redir_node->s_operator.right->s_command.argv[0]) == 0)
		{
			free(u_input);
			break ;
		}
		write(pipe_fd[1], u_input, ft_strlen(u_input));
		write(pipe_fd[1], "\n", 1);
		free(u_input);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (0);
}

int	exec_redir(t_ast_node *redir_node, t_env_map *envs)
{
	int	saved_stdin;
	int	saved_stdout;
	int	res;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (throw_redir_error(0, STDIN_FILENO, STDOUT_FILENO));
	if (redir_node->s_operator.op_type == REDIR_IN
		&& handle_redir_in(redir_node, saved_stdin, saved_stdout) != 0)
		return (1);
	else if (redir_node->s_operator.op_type == REDIR_OUT
		&& handle_redir_out(redir_node, saved_stdin, saved_stdout) != 0)
		return (1);
	else if (redir_node->s_operator.op_type == APPEND
		&& handle_redir_append(redir_node, saved_stdin, saved_stdout) != 0)
		return (1);
	else if (redir_node->s_operator.op_type == HEREDOC
		&& handle_redir_heredoc(redir_node, saved_stdin, saved_stdout) != 0)
		return (1);
	else if (!is_redir(redir_node->s_operator.op_type))
		return (throw_redir_error(5, saved_stdin, saved_stdout));
	res = execute_ast_tree(redir_node->s_operator.left, envs);
	reset_std(saved_stdin, saved_stdout);
	return (res);
}
