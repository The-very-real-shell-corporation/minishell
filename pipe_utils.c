/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 19:46:35 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/14 14:43:52 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_single_pipe(t_data *data, int *fd)
{
	if (pipe(fd) == -1)
		exit_error(data, "pipe not piping");
}

void	duplicate_fd(t_data *data, int old, int new)
{
	if (dup2(old, new) == -1)
		exit_error(data, "dup2 failed");
	close(old);
}

void	close_main_fds(int pipe_fds[2][2])
{
	if (pipe_fds[1][0] != -1)
	{
		close(pipe_fds[1][READ]);
		close(pipe_fds[1][WRITE]);
	}
}
