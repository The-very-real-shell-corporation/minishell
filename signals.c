/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 15:16:19 by akasiota      #+#    #+#                 */
/*   Updated: 2024/02/19 17:40:23 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Global is required to save the exit status when not actually
	exiting a child process, but when pressing ctrl c	*/

int	*g_exit_status;

void	set_signals(t_data *data)
{
	g_exit_status = &data->exit_status;
	signal(SIGINT, &signal_int_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	unset_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_for_kids(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_int_handler(int sig)
{
	(void)sig;
	*g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("\0", 0);
	rl_redisplay();
}
