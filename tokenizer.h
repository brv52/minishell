/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:50:44 by borov             #+#    #+#             */
/*   Updated: 2024/12/25 21:10:15 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "utilities.h"

# define __OP_LAST_IDX 4

typedef enum token_type
{
	PIPE,
	OR,
	AND,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	WORD,
	S_QUOTE,
	D_QUOTE,
	L_BRACKET,
	R_BRACKET,
	UNDEFINED
}	t_token_type;

typedef struct token
{
	t_string		data;
	t_token_type	type;
	struct token	*next;
}	t_token;

t_token			*tokenize(t_string *u_promt);
void			destroy_token(t_token *token);
void			destroy_tokens(t_token *tokens);
int				handle_quotes(t_string *u_promt, size_t *c_pos, t_token *new);
int				handle_metacharacters(t_string *u_promt,
					size_t *c_pos, t_token *new);
int				handle_words(t_string *u_promt, size_t *c_pos, t_token *new);
int				handle_token(t_string *u_promt, size_t *c_pos, t_token *new);
t_token_type	get_token_type(t_string *str);

#endif
