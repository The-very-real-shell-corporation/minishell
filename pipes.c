/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 20:31:02 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_pipeline(t_data *data, t_mlist *input, t_token tolkien)
{
	char 	**result;

	result = list_to_array(data, input, PIPE);
	while (input != NULL && input->token != PIPE)
		input = input->nx;
	node_addback(&data->pipelines, new_node(data, NULL, result, tolkien));
	if (input != NULL)
	{
		input = input->nx;
		build_pipeline(data, input, input->token);
	}
}

pid_t	fork_pipe(t_data *data, t_mlist *pipelines)
{
	pid_t	id;

	id = create_fork(data);
	if (id == 0)
	{
		close_extra_fds(data->pipe_fds);
		copy_pipe_fds(data, data->pipe_fds);
		if (run_builtins(data, pipelines) == false)
			search_the_path(data, pipelines, data->path);
		exit(55);
	}
	return (id);
}
