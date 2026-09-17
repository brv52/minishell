/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:42:13 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:58:35 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token_type	get_token_type(t_string *str)
{
	if (!str || !str->data)
		return (UNDEFINED);
	if (cmp_str_data(str->data, "|") == 0)
		return (PIPE);
	else if (cmp_str_data(str->data, "||") == 0)
		return (OR);
	else if (cmp_str_data(str->data, "&&") == 0)
		return (AND);
	else if (cmp_str_data(str->data, "<") == 0)
		return (REDIR_IN);
	else if (cmp_str_data(str->data, ">") == 0)
		return (REDIR_OUT);
	else if (cmp_str_data(str->data, "<<") == 0)
		return (HEREDOC);
	else if (cmp_str_data(str->data, ">>") == 0)
		return (APPEND);
	else if (str->data && str->data[0] == '(')
		return (L_BRACKET);
	else if (str->data && str->data[0] == ')')
		return (R_BRACKET);
	return (WORD);
}

void	destroy_token(t_token *token)
{
	destroy_str(&token->data);
	free_memo((void **)&token);
}

void	destroy_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || tokens == NULL)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		destroy_token(current);
		current = next;
	}
}

static void	*handle_err(t_token *new, t_token *head)
{
	destroy_token(new);
	destroy_tokens(head);
	return (NULL);
}

t_token	*tokenize(t_string *u_promt)
{
	t_token	*head;
	t_token	**current;
	t_token	*new;
	size_t	c_pos;

	head = NULL;
	current = &head;
	c_pos = 0;
	while (c_pos < u_promt->size)
	{
		if (u_promt->data[c_pos] == ' ')
		{
			c_pos += 1;
			continue ;
		}
		new = (t_token *)malloc(sizeof(t_token));
		new->next = NULL;
		if (handle_token(u_promt, &c_pos, new) != 0)
			return (handle_err(new, head));
		*current = new;
		current = &new->next;
	}
	return (head);
}
