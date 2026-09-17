/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:07:03 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 20:57:32 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "utilities.h"
# include "environmentals.h"

int	bin_echo(char **argv, t_env_map *envs);
int	bin_cd(char **argv, t_env_map *envs);
int	bin_pwd(t_env_map *envs);
int	bin_export(char **argv, t_env_map *envs);
int	bin_unset(char **argv, t_env_map *envs);
int	bin_env(char **argv, t_env_map *envs);
int	bin_exit(char **argv);

#endif
