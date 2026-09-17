/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_helpers_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:16:59 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:51:30 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*crt_op_node(t_token_type type,
			t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*op_node;

	op_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	op_node->node_type = OPERATOR;
	op_node->s_operator.op_type = type;
	op_node->s_operator.left = left;
	op_node->s_operator.right = right;
	return (op_node);
}

static void	decide_free(t_ast_node *left, t_ast_node *right)
{
	if (left)
		destroy_ast_tree(left);
	if (right)
		destroy_ast_tree(right);
}

static int	throw_sy_error(int err_code)
{
	if (err_code == 0)
		write(STDERR_FILENO, "parser_error: operator stack is empty\n", 38);
	else if (err_code == 1)
		write(STDERR_FILENO, "parser_error: missmatched paratheses\n", 37);
	else if (err_code == 2)
		write(STDERR_FILENO, "parser_error: not enough operands\n", 34);
	return (1);
}

int	pop_crt_node(t_stack *op_stack, t_stack *out_stack)
{
	t_token		*op_token;
	t_ast_node	*left;
	t_ast_node	*right;

	op_token = (t_token *)st_pop(op_stack);
	if (!op_token)
		return (throw_sy_error(0));
	if (op_token->type == L_BRACKET)
		return (throw_sy_error(1));
	left = NULL;
	right = (t_ast_node *)st_pop(out_stack);
	if (is_op(op_token->type))
	{
		left = (t_ast_node *)st_pop(out_stack);
		if (!left || !right)
		{
			decide_free(left, right);
			return (throw_sy_error(2));
		}
	}
	st_push(out_stack, crt_op_node(op_token->type, left, right), 1);
	return (0);
}
