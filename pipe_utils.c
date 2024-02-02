/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 19:46:35 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/02 16:07:12 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_single_pipe(t_data *data, int *fd)
{
	if (pipe(fd) == -1)
		exit_error(data, "pipe not piping");
}

void	open_pipe(t_data *data, int position)
{
	int	*fd[2];

	fd[0] = data->pipe_fds[0];
	fd[1] = data->pipe_fds[1];
	if (position == START)
	{
		open_single_pipe(data, fd[0]);
		fd[1][READ] = -1;
		fd[1][WRITE] = -1;
	}
	if (position == MIDDLE)
	{
		fd[1][READ] = fd[0][READ];
		fd[1][WRITE] = fd[0][WRITE];
		open_single_pipe(data, fd[0]);
	}
	if (position == END)
	{
		fd[1][READ] = fd[0][READ];
		fd[1][WRITE] = fd[0][WRITE];
		fd[0][READ] = -1;
		fd[0][WRITE] = -1;
	}
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
