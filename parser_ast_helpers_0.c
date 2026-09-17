/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_helpers_0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:16:52 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:51:30 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_op(t_token_type token_type)
{
	return (token_type >= 0 && token_type <= 7);
}

int	is_redir(t_token_type token_type)
{
	return (token_type >= 3 && token_type <= 6);
}

int	get_op_priority(t_token_type type)
{
	if (type == PIPE)
		return (0);
	if (type == OR || type == AND)
		return (1);
	if (is_redir(type))
		return (2);
	return (-1);
}
