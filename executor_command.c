/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:01:23 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 05:29:45 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	destroy_dirs(char **dirs, t_string *test_path)
{
	size_t	c_path;

	c_path = 0;
	while (dirs && dirs[c_path])
	{
		free_memo((void **)&dirs[c_path]);
		c_path += 1;
	}
	if (dirs)
		free_memo((void **)&dirs);
	if (test_path)
		destroy_str(test_path);
}

static int	exec_absolute(t_ast_node *op_node, t_env_map *envs)
{
	char		**path_dirs;
	t_string	test_path;
	size_t		c_path;

	if (env_get(envs, "PATH") != NULL)
		path_dirs = ft_slash_split(env_get(envs, "PATH")->key_val[1].data, ':');
	else
		path_dirs = NULL;
	c_path = 0;
	while (path_dirs && path_dirs[c_path])
	{
		test_path = str_cat(path_dirs[c_path], op_node->s_command.argv[0]);
		if (access(test_path.data, X_OK) == 0)
		{
			free_memo((void **)&op_node->s_command.argv[0]);
			op_node->s_command.argv[0] = cp_str_data(test_path.data);
			destroy_dirs(path_dirs, &test_path);
			return (execve(op_node->s_command.argv[0],
					op_node->s_command.argv, NULL));
		}
		destroy_str(&test_path);
		c_path += 1;
	}
	destroy_dirs(path_dirs, NULL);
	return (1);
}

static int	exec_child(t_ast_node *op_node, t_env_map *envs)
{
	int	exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (op_node->s_command.argv[0][0] == '/')
		exit_status = execve(op_node->s_command.argv[0],
				op_node->s_command.argv, NULL);
	else
		exit_status = exec_absolute(op_node, envs);
	if (exit_status != 0)
		write(STDERR_FILENO, "excecve_error: failed\n", 22);
	exit(exit_status != 0);
}

static int	exec_parent(int pid, int *status, t_ast_node *op_node)
{
	int	sig;

	signal(SIGINT, second_hand);
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		if (sig == SIGQUIT)
			printf("Quit    %s\n", op_node->s_command.argv[0]);
		else if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (WEXITSTATUS(*status));
}

int	exec_command(t_ast_node *op_node, t_env_map *envs)
{
	pid_t	pid;
	int		status;
	int		bin_id;

	if (expand_args(op_node->s_command.argv,
			op_node->s_command.types, envs) != 0)
		return (1);
	bin_id = is_bin(op_node);
	if (bin_id != 0)
		return (exec_bin(op_node, envs, bin_id));
	pid = fork();
	if (pid == 0)
		exec_child(op_node, envs);
	else
		return (exec_parent(pid, &status, op_node));
	return (1);
}
