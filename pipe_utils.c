/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 19:46:35 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/23 15:31:31 by vvan-der      ########   odam.nl         */
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
	if (pipes == START)
	{
		open_single_pipe(data, fd[0]);
		fd[1][0] = -1;
		fd[1][1] = -1;
	}
	if (pipes == MIDDLE)
	{
		fd[1][0] = fd[0][0];
		fd[1][1] = fd[0][1];
		open_single_pipe(data, fd[0]);
	}
	if (pipes == END)
	{
		fd[1][0] = fd[0][0];
		fd[1][1] = fd[0][1];
		fd[0][0] = -1;
		fd[0][1] = -1;
	}
}

void	direct_pipes_left(t_data *data, int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
	{
		close(data->pipe_fds[0][1]);
		if (dup2(pipe_fds[0][0], STDIN_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[0][0]);
	}
	if (pipe_fds[1][0] != -1)
	{
		close(data->pipe_fds[1][0]);
		if (dup2(pipe_fds[1][1], STDOUT_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[1][1]);
	}
}

void	direct_pipes_right(t_data *data, int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
	{
		close(data->pipe_fds[0][0]);
		if (dup2(pipe_fds[0][1], STDOUT_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[0][1]);
	}
	if (pipe_fds[1][0] != -1)
	{
		close(data->pipe_fds[1][1]);
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
