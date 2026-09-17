/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 21:02:42 by borov             #+#    #+#             */
/*   Updated: 2024/12/25 21:13:20 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug_minishell.h"

void	print_type(t_token_type type)
{
	if (type == WORD)
		printf("type: WORD");
	if (type == PIPE)
		printf("type: PIPE");
	if (type == OR)
		printf("type: OR");
	if (type == AND)
		printf("type: AND");
	if (type == REDIR_IN)
		printf("type: REDIR_IN");
	if (type == REDIR_OUT)
		printf("type: REDIR_OUT");
	if (type == HEREDOC)
		printf("type: HEREDOC");
	if (type == APPEND)
		printf("type: APPEND");
	if (type == S_QUOTE)
		printf("type: S_QUOTE");
	if (type == D_QUOTE)
		printf("type: D_QUOTE");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		printf("token got: [%s] ", current->data.data);
		print_type(current->type);
		printf("\n");
		current = next;
	}
}

void	print_ast(t_ast_node *node, int indent)
{
	if (node == NULL) return;

	for (int i = 0; i < indent; i++) printf("  ");

	if (node->node_type == COMMAND) {
		printf("Command: ");
		for (size_t i = 0; i < node->s_command.argc; i++) {
			printf("%s ", node->s_command.argv[i]);
		}
		printf("\n");
	}
	else if (node->node_type == OPERATOR) {
		printf("Operator: ");
		switch (node->s_operator.op_type) {
			case PIPE:
				printf("|\n");
				break;
			case OR:
				printf("||\n");
				break;
			case AND:
				printf("&&\n");
				break;
			case REDIR_IN:
				printf("<\n");
				break;
			case REDIR_OUT:
				printf(">\n");
				break;
			case APPEND:
				printf(">>\n");
				break;
			case HEREDOC:
				printf("<<\n");
				break;
			default:
				printf("Unknown operator\n");
				break;
		}
		print_ast(node->s_operator.left, indent + 1);
		print_ast(node->s_operator.right, indent + 1);
	}
}
