/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 19:46:35 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/08 19:48:58 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	pipeline_size(t_mlist *input)
{
	size_t	i;

	i = 0;
	while (input != NULL && (input)->token != PIPE) 
	{
		i++;
		input = (input)->nx;
	}
	return (i);
}

void	create_pipe_fds(t_data *data, int pipes)
{
	int	**fds;
	int	i;

	i = 0;
	fds = ft_calloc(pipes + 1, sizeof(int*));
	if (fds == NULL)
		exit_error(data, "malloc failed");
	while (i < pipes)
	{
		fds[i] = ft_calloc(2, sizeof(int));
		if (fds[i] == NULL)
			exit_error(data, "malloc failed");
		i++;
	}
	data->pipe_fds = fds;
}

void	open_pipes(t_data *data, int **pipe_fds)
{
	int i;

	i = 0;	
	while (pipe_fds[i] != NULL)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			while (i >= 0)
			{
				close(pipe_fds[i][0]);
				close(pipe_fds[i][1]);
				i--;
			}
			exit_error(data, "pipe failed to pipe");
		}
		i++;
	}
}

void	close_pipes(int **pipe_fds)
{
	int	i = 0;
	while (pipe_fds[i] != NULL)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}