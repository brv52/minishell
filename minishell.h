/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:15:58 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 02:10:16 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utilities.h"
# include "input_handler.h"
# include "tokenizer.h"
# include "parser.h"
# include "executor.h"
# include "environmentals.h"
# include "built_in.h"
# include "signal_handler.h"

typedef struct shell_data
{
	t_string	u_promt;
	t_token		*tokens;
	t_ast_node	*ast_tree;
	t_env_map	envs;
}	t_shell_data;

#endif
