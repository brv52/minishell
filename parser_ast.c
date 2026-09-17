/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:29:19 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 03:05:25 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*crt_command(t_token *current)
{
	t_ast_node	*cur_cmd_node;

	cur_cmd_node = (t_ast_node *)malloc(sizeof(t_ast_node));
	cur_cmd_node->node_type = COMMAND;
	cur_cmd_node->s_command.argv = (char **)malloc(sizeof(char *) * 2);
	cur_cmd_node->s_command.types = (t_token_type *)malloc
		(sizeof(t_token_type) * 2);
	cur_cmd_node->s_command.argv[0] = cp_str_data(current->data.data);
	cur_cmd_node->s_command.types[0] = current->type;
	cur_cmd_node->s_command.types[1] = UNDEFINED;
	cur_cmd_node->s_command.argv[1] = NULL;
	cur_cmd_node->s_command.argc = 1;
	return (cur_cmd_node);
}

void	add_arg(t_ast_node *cur_cmd_node, t_token *current)
{
	size_t			c_arg;
	char			**n_argv;
	t_token_type	*n_types;

	c_arg = 0;
	n_argv = (char **)malloc
		(sizeof(char *) * (cur_cmd_node->s_command.argc + 2));
	n_types = (t_token_type *)malloc
		(sizeof(t_token_type) * (cur_cmd_node->s_command.argc + 2));
	while (c_arg < cur_cmd_node->s_command.argc)
	{
		n_argv[c_arg] = cp_str_data(cur_cmd_node->s_command.argv[c_arg]);
		free_memo((void **)&cur_cmd_node->s_command.argv[c_arg]);
		n_types[c_arg] = cur_cmd_node->s_command.types[c_arg];
		c_arg += 1;
	}
	n_argv[c_arg] = cp_str_data(current->data.data);
	n_types[c_arg] = current->type;
	n_argv[c_arg + 1] = NULL;
	n_types[c_arg + 1] = UNDEFINED;
	free_memo((void **)&cur_cmd_node->s_command.argv);
	free_memo((void **)&cur_cmd_node->s_command.types);
	cur_cmd_node->s_command.argv = n_argv;
	cur_cmd_node->s_command.types = n_types;
	cur_cmd_node->s_command.argc += 1;
}

int	cleanup_parser(t_parser_state *state, int err_code)
{
	write(STDERR_FILENO, "parser_error: ", 14);
	if (err_code == 0)
		write(STDERR_FILENO, "redirection without command\n", 28);
	if (err_code == 1)
		write(STDERR_FILENO, "filename expected\n", 18);
	if (err_code == 2)
		write(STDERR_FILENO, "mismatched parantheses\n", 23);
	if (err_code == 3)
		write(STDERR_FILENO, "unknown token type\n", 19);
	if (err_code == 4)
		write(STDERR_FILENO, "multiple nodes left on out stack\n", 33);
	if (err_code == 5)
		write(STDERR_FILENO, "empty out stack\n", 16);
	destroy_stack(&state->op_stack);
	destroy_stack(&state->out_stack);
	if (err_code != -1 && err_code != 2 && err_code != 1 && state->cur_cmd_node)
	{
		destroy_ast_tree(state->cur_cmd_node);
		state->cur_cmd_node = NULL;
	}
	return (-1);
}

t_ast_node	*get_root(t_parser_state *state)
{
	t_ast_node	*root;

	while (!is_empty(&state->op_stack))
	{
		if (pop_crt_node(&state->op_stack, &state->out_stack) != 0)
		{
			state->ret_state = cleanup_parser(state, -1);
			return (NULL);
		}
	}
	if (!is_empty(&state->out_stack))
	{
		root = (t_ast_node *)st_pop(&state->out_stack);
		if (!is_empty(&state->out_stack))
		{
			state->ret_state = cleanup_parser(state, 4);
			return (NULL);
		}
		return (root);
	}
	else
	{
		state->ret_state = cleanup_parser(state, 5);
		return (NULL);
	}
}

t_ast_node	*parse_tokens(t_token *tokens)
{
	t_parser_state	state;

	initialize_parser(&state, tokens);
	while (state.current)
	{
		if (state.current->type >= 7 && state.current->type <= 9)
			handle_word(&state);
		else if (state.current->type == L_BRACKET)
			handle_l_bracket(&state);
		else if (state.current->type == R_BRACKET)
			handle_r_bracket(&state);
		else if (is_op(state.current->type))
			handle_op(&state);
		else
			state.ret_state = cleanup_parser(&state, 3);
		if (state.ret_state == -1)
			return (NULL);
		state.current = state.current->next;
	}
	return (get_root(&state));
}
