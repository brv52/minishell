/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:57:27 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:51:30 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "environmentals.h"
# include "parser.h"

int	expand_args(char **argv, t_token_type *types, t_env_map *envs);

#endif
