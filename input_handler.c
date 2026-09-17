/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:01:07 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 23:03:06 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_handler.h"

static void	prep_promt_data(t_string *u_promt)
{
	free_memo((void **)&u_promt->data);
	init_str(u_promt);
}

static char	*line_read(int status)
{
	if (status == 0)
		return (readline(__BEG_PROMT_SUCCESS));
	else
		return (readline(__BEG_PROMT_FAIL));
}

void	read_input(t_string *u_promt, int status)
{
	char	*input;

	prep_promt_data(u_promt);
	input = line_read(status);
	if (!input)
	{
		init_str(u_promt);
		return ;
	}
	if (*input == '\0')
	{
		u_promt->data = malloc(1);
		u_promt->data[0] = '\0';
		u_promt->size = 0;
		free(input);
		return ;
	}
	if (input)
	{
		add_history(input);
		*u_promt = create_string(input, ft_strlen(input));
	}
	free(input);
}
