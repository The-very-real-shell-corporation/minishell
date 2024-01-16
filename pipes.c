/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/16 19:44:59 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mlist	*check_heredoc(t_data *data, t_mlist *input)
{
	t_mlist	*doc;
	t_mlist	*tmp;

	tmp = NULL;
	if (input->token == HEREDOC)
	{
		doc = whatsup_doc(data, input);
		if (doc != NULL)
		{	
			tmp = input->nx->nx;
			insert_node(input, input->nx, doc);
		}
		unlink_node(input->nx);
		unlink_node(input);
		return (tmp);
	}
	else
		return (input->nx);
}

void	build_pipeline(t_data *data, t_mlist *input, t_mlist **pipelines)
{
	char 	**result;
	t_token	tolkien;

	tolkien = input->token;
	while (input != NULL && input->token != PIPE)
	{
		input = check_heredoc(data, input);	
	}
	result = list_to_array(data, input, PIPE);
	if (result != NULL)
		node_addback(&data->pipelines, new_node(data, NULL, result, tolkien));
	if (input != NULL)
		build_pipeline(data, input->nx, pipelines + 1);
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
