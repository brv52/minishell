/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:16:25 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:29:02 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_argv(t_ast_node *node)
{
	size_t	c_arg;

	c_arg = 0;
	while (c_arg < node->s_command.argc)
	{
		free_memo((void **)&node->s_command.argv[c_arg]);
		c_arg += 1;
	}
	free_memo((void **)&node->s_command.argv);
	free_memo((void **)&node->s_command.types);
	node->s_command.argv = NULL;
	node->s_command.argc = 0;
}

void	destroy_ast_tree(t_ast_node *node)
{
	if (node == NULL || !node)
		return ;
	if (node->node_type == COMMAND)
		free_argv(node);
	else if (node->node_type == OPERATOR)
	{
		destroy_ast_tree(node->s_operator.left);
		destroy_ast_tree(node->s_operator.right);
	}
	free_memo((void **)&node);
}
