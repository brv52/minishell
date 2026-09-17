/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_helpers_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:24:55 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 03:05:25 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	initialize_parser(t_parser_state *state, t_token *tokens)
{
	state->current = tokens;
	state->cur_cmd_node = NULL;
	state->ret_state = 0;
	st_init(&state->op_stack);
	st_init(&state->out_stack);
}

void	handle_word(t_parser_state *state)
{
	if (state->cur_cmd_node == NULL)
	{
		state->cur_cmd_node = crt_command(state->current);
		st_push(&state->out_stack, state->cur_cmd_node, 1);
	}
	else
		add_arg(state->cur_cmd_node, state->current);
}

void	handle_l_bracket(t_parser_state *state)
{
	state->cur_cmd_node = NULL;
	st_push(&state->op_stack, state->current, 0);
}

void	handle_r_bracket(t_parser_state *state)
{
	while (!is_empty(&state->op_stack)
		&& ((t_token *)peek(&state->op_stack))->type != L_BRACKET
		&& get_op_priority(state->current->type) < get_op_priority((
				(t_token *)peek(&state->op_stack))->type))
	{
		if (pop_crt_node(&state->op_stack, &state->out_stack) != 0)
		{
			state->ret_state = cleanup_parser(state, -1);
			return ;
		}
	}
	if (is_empty(&state->op_stack))
	{
		state->ret_state = cleanup_parser(state, 2);
		return ;
	}
	st_pop(&state->op_stack);
}

void	handle_op(t_parser_state *state)
{
	state->cur_cmd_node = NULL;
	while (!is_empty(&state->op_stack)
		&& is_op(((t_token *)peek(&state->op_stack))->type)
		&& get_op_priority(((t_token *)peek(&state->op_stack))->type)
		>= get_op_priority(state->current->type))
	{
		if (pop_crt_node(&state->op_stack, &state->out_stack) != 0)
		{
			state->ret_state = (cleanup_parser(state, -1));
			return ;
		}
	}
	st_push(&state->op_stack, state->current, 0);
}
