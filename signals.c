/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borov <borov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:37:29 by borov             #+#    #+#             */
/*   Updated: 2024/12/24 22:38:27 by borov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "parser.h"

void	handle_signal(int signo)
{
	g_signal = signo;
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	second_hand(int signo)
{
	g_signal = signo;
}

void	sig_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	piping_sign(int status[2], t_ast_node *pipe_node)
{
	if (WIFSIGNALED(status[0]))
	{
		g_signal = WTERMSIG(status[0]);
		if (g_signal == SIGQUIT)
			printf("quit   %s\n", pipe_node->s_command.argv[0]);
		else if (g_signal == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (WIFSIGNALED(status[1]))
	{
		g_signal = WTERMSIG(status[1]);
		if (g_signal == SIGQUIT)
			printf("quit   %s\n", pipe_node->s_command.argv[1]);
		else if (g_signal == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
