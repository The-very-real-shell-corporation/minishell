/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 17:51:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_pipelines(t_data *data, t_mlist *in, t_mlist **pipelines)
{
	char	**arr;

	while (in != NULL)
	{
		arr = list_to_array(data, in);
		if (arr != NULL)
			node_addback(pipelines, new_node(data, NULL, arr, in->token));
		while (in != NULL && is_redirection(in->token) == NONE)
			in = in->nx;
		if (in != NULL && is_redirection(in->token) != NONE)
		{
			node_addback(pipelines, copy_node(data, in));
			in = in->nx;
		}
	}
}

void	direct_pipes_left(t_data *data, int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
	{
		close(data->pipe_fds[0][1]);
		duplicate_fd(data, pipe_fds[0][0], STDIN_FILENO);
		close(data->pipe_fds[0][0]);
	}
	if (pipe_fds[1][0] != -1)
	{
		close(data->pipe_fds[1][0]);
		duplicate_fd(data, pipe_fds[1][1], STDOUT_FILENO);
		close(data->pipe_fds[1][1]);
	}
}

void	direct_pipes_right(t_data *data, int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
	{
		close(data->pipe_fds[0][0]);
		duplicate_fd(data, pipe_fds[0][1], STDOUT_FILENO);
		close(data->pipe_fds[0][1]);
	}
	if (pipe_fds[1][0] != -1)
	{
		close(data->pipe_fds[1][1]);
		duplicate_fd(data, pipe_fds[1][0], STDIN_FILENO);
		close(data->pipe_fds[1][0]);
	}
}
