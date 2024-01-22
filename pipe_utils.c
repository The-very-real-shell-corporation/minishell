/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 19:46:35 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/22 18:15:42 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_single_pipe(t_data *data, int *fd)
{
	if (pipe(fd) == -1)
		exit_error(data, "pipe not piping");
}

void	open_pipe(t_data *data, int pipes)
{
	int	*fd[2];

	fd[0] = data->pipe_fds[0];
	fd[1] = data->pipe_fds[1];
	if (pipes == 0)
	{
		open_single_pipe(data, fd[0]);
		fd[1][0] = -1;
		fd[1][1] = -1;
	}
	if (pipes == 1)
	{
		fd[1][0] = fd[0][0];
		fd[1][1] = fd[0][1];
		fd[0][0] = -1;
		fd[0][1] = -1;
	}
	if (pipes == 2)
	{
		fd[1][0] = fd[0][0];
		fd[1][1] = fd[0][1];
		open_single_pipe(data, fd[0]);
	}
}

void	close_extra_fds(int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
		close(pipe_fds[0][0]);
	if (pipe_fds[1][1] != -1)
		close(pipe_fds[1][1]);
}

void	copy_pipe_fds(t_data *data, int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
	{
		if (dup2(pipe_fds[0][1], STDOUT_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[0][1]);
	}
	if (pipe_fds[1][0] != -1)
	{
		if (dup2(pipe_fds[1][0], STDIN_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[1][0]);
	}
}

void	close_main_fds(int pipe_fds[2][2])
{
	if (pipe_fds[1][0] != -1)
	{
		close(pipe_fds[1][0]);
		close(pipe_fds[1][1]);
	}
}
