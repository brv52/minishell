/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:09:42 by borov             #+#    #+#             */
/*   Updated: 2024/12/25 21:13:02 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MINISHELL_H
# define DEBUG_MINISHELL_H

# include "../minishell.h"

void	print_type(t_token_type type);
void	print_tokens(t_token *tokens);
void	print_ast(t_ast_node *node, int indent);

#endif