/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 17:19:28 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_pipes_pipe(t_data *data, int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
	{
		close(data->pipe_fds[0][READ]);
		duplicate_fd(data, pipe_fds[0][WRITE], STDOUT_FILENO);
		close(data->pipe_fds[0][WRITE]);
	}
	if (pipe_fds[1][0] != -1)
	{
		close(data->pipe_fds[1][WRITE]);
		duplicate_fd(data, pipe_fds[1][READ], STDIN_FILENO);
		close(data->pipe_fds[1][READ]);
	}
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
