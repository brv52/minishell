/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:23:13 by borov             #+#    #+#             */
/*   Updated: 2024/12/26 03:05:25 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "utilities.h"
# include "tokenizer.h"
# include "redirections.h"

typedef enum ast_node_type
{
	COMMAND,
	OPERATOR
}	t_ast_node_type;

typedef enum op_priority
{
	OP_PIPE,
	OP_REDIR_IN,
	OP_REDIR_OUT,
	OP_APPEND,
	OP_HEREDOC
}	t_op_priority;

typedef struct ast_node
{
	t_ast_node_type	node_type;
	union
	{
		struct
		{
			char			**argv;
			t_token_type	*types;
			size_t			argc;
		}	s_command;
		struct
		{
			t_token_type	op_type;
			struct ast_node	*left;
			struct ast_node	*right;
		}	s_operator;
	};
}	t_ast_node;

typedef struct node_stack
{
	void				*data;
	int					type;
	struct node_stack	*next;
}	t_node_stack;

typedef struct stack
{
	t_node_stack	*top;
}	t_stack;

typedef struct parser_state
{
	t_token			*current;
	t_ast_node		*cur_cmd_node;
	t_stack			op_stack;
	t_stack			out_stack;
	int				ret_state;
}	t_parser_state;

void		st_init(t_stack *st);
void		destroy_node(t_node_stack *node);
void		destroy_stack(t_stack *st);
void		st_push(t_stack *st, void *data, int type);
void		*st_pop(t_stack *st);
void		*peek(t_stack *st);
int			is_empty(t_stack *st);
int			is_op(t_token_type token_type);
int			is_redir(t_token_type token_type);
int			get_op_priority(t_token_type type);
int			pop_crt_node(t_stack *op_stack, t_stack *out_stack);
t_ast_node	*parse_tokens(t_token *tokens);
void		destroy_ast_tree(t_ast_node *node);
void		handle_word(t_parser_state *state);
void		handle_l_bracket(t_parser_state *state);
void		handle_r_bracket(t_parser_state *state);
void		handle_op(t_parser_state *state);
void		initialize_parser(t_parser_state *state, t_token *tokens);
t_ast_node	*crt_command(t_token *current);
void		add_arg(t_ast_node *cur_cmd_node, t_token *current);
int			cleanup_parser(t_parser_state *state, int err_code);

#endif
