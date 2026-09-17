/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:35:46 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:37:06 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include "utilities.h"
# include "parser.h"

extern sig_atomic_t	g_signal;

void	handle_signal(int signo);
void	sig_init(void);
void	second_hand(int signo);
void	piping_sign(int status[2], t_ast_node *pipe_node);

#endif