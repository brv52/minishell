/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handlers_0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:49:14 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:50:28 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	handle_quotes(t_string *u_promt, size_t *c_pos, t_token *new)
{
	char	quote;
	size_t	start;

	quote = u_promt->data[*c_pos];
	*c_pos += 1;
	start = *c_pos;
	while (*c_pos < u_promt->size && u_promt->data[*c_pos] != quote)
		*c_pos += 1;
	if (u_promt->data[*c_pos] != quote)
	{
		write(STDERR_FILENO, "tokenizer_error: non-closed quotes\n", 35);
		new->data.data = NULL;
		return (1);
	}
	new->data = create_string(&u_promt->data[start], *c_pos - start);
	*c_pos += 1;
	if (quote == '\'')
		new->type = S_QUOTE;
	else if (quote == '"')
		new->type = D_QUOTE;
	return (0);
}

int	handle_metacharacters(t_string *u_promt, size_t *c_pos, t_token *new)
{
	if ((u_promt->data[*c_pos] == '&'
			|| u_promt->data[*c_pos] == '|'
			|| u_promt->data[*c_pos] == '<'
			|| u_promt->data[*c_pos] == '>')
		&& u_promt->data[*c_pos + 1] == u_promt->data[*c_pos])
	{
		new->data = create_string(&u_promt->data[*c_pos], 2);
		*c_pos += 2;
	}
	else
	{
		new->data = create_string(&u_promt->data[*c_pos], 1);
		*c_pos += 1;
	}
	return (0);
}

int	handle_words(t_string *u_promt, size_t *c_pos, t_token *new)
{
	size_t	start;

	start = *c_pos;
	while (*c_pos < u_promt->size
		&& u_promt->data[*c_pos] != ' '
		&& str_chr(u_promt->data[*c_pos], __METACHARS) == -1
		&& u_promt->data[*c_pos] != '\''
		&& u_promt->data[*c_pos] != '"')
		*c_pos += 1;
	new->data = create_string(&u_promt->data[start], *c_pos - start);
	return (0);
}

int	handle_token(t_string *u_promt, size_t *c_pos, t_token *new)
{
	int	validation_error;

	new->type = UNDEFINED;
	if (u_promt->data[*c_pos] == '\'' || u_promt->data[*c_pos] == '"')
		validation_error = handle_quotes(u_promt, c_pos, new);
	else if (str_chr(u_promt->data[*c_pos], __METACHARS) != -1)
		validation_error = handle_metacharacters(u_promt, c_pos, new);
	else
		validation_error = handle_words(u_promt, c_pos, new);
	if (new->type == UNDEFINED)
		new->type = get_token_type(&new->data);
	return (validation_error);
}
