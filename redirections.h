/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:35:30 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:51:30 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "utilities.h"

typedef struct redir
{
	t_token_type	redir_type;
	t_string		filename;
	struct redir	*next;
}	t_redirection;

#endif
