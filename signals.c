/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 15:16:19 by akasiota      #+#    #+#                 */
/*   Updated: 2024/02/06 18:23:07 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_parent_ctrlc(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	set_signals(void)
{
	signal(SIGINT, &signal_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	unset_signals(void)
{
	signal(SIGINT, &signal_handler_parent_ctrlc);
	signal(SIGQUIT, &signal_handler_parent_ctrlc);
}

void	signals_for_kids(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_int_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}
