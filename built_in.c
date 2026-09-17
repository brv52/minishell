/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:07:26 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 23:08:14 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	bin_echo(char **argv, t_env_map *envs)
{
	size_t	c_arg;
	int		n_flag;

	if (!argv || !argv[0] || !envs)
		return (1);
	if (argv[1] && cmp_str_data(argv[1], "-n") == 0)
		n_flag = 1;
	else
		n_flag = 0;
	c_arg = n_flag + 1;
	while (argv[c_arg] != NULL)
	{
		printf("%s", argv[c_arg]);
		if (argv[c_arg] && argv[c_arg + 1] != NULL)
			printf(" ");
		c_arg += 1;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

static int	upd_pwd(t_env_map *envs)
{
	t_env	*path;
	char	*n_pwd;

	path = env_get(envs, "PWD");
	n_pwd = getcwd(NULL, 0);
	if (path != NULL)
	{
		destroy_str(&path->key_val[1]);
		path->key_val[1] = create_string(n_pwd, ft_strlen(n_pwd));
		free(n_pwd);
	}
	else
	{
		perror("upd_pwd error\n");
		free(n_pwd);
		return (1);
	}
	return (0);
}

int	bin_cd(char **argv, t_env_map *envs)
{
	char	*dir;

	if (!argv || (argv[1] && argv[2]))
	{
		write(STDERR_FILENO, "cd_error: invalid arguments\n", 28);
		return (1);
	}
	if (!argv[1])
	{
		dir = (env_get(envs, "HOME"))->key_val[1].data;
		if (!dir)
		{
			write(STDERR_FILENO, "cd_error: HOME not set\n", 23);
			return (1);
		}
	}
	else
		dir = argv[1];
	if (chdir(dir))
	{
		write(STDERR_FILENO, "cd_error: cannot change directory\n", 34);
		return (1);
	}
	return (upd_pwd(envs));
}

int	bin_pwd(t_env_map *envs)
{
	t_env	*cwd;

	cwd = env_get(envs, "PWD");
	if (!cwd)
	{
		write(STDERR_FILENO, "pwd_error: cannot find PWD\n", 27);
		return (1);
	}
	printf("PWD: %s\n", cwd->key_val[1].data);
	return (0);
}

int	bin_exit(char **argv)
{
	if (!argv || !argv[0] || argv[1])
	{
		write(STDERR_FILENO, "exit_error: invalid arguments\n", 30);
		return (1);
	}
	exit(0);
	return (0);
}
