/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/22 20:38:28 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static t_mlist	*check_heredoc(t_data *data, t_mlist *input)
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
} */

void	build_pipelines(t_data *data, t_mlist *in, t_mlist **pipelines)
{
	char 	**arr;

	while (in != NULL)
	{
		arr = list_to_array(data, in);
		if (arr != NULL)
			node_addback(pipelines, new_node(data, NULL, arr, in->token));
		while (in != NULL && is_redirection(in->token) == false)
			in = in->nx;
		if (in != NULL && is_redirection(in->token) == true)
		{
			node_addback(pipelines, new_node(data, NULL, NULL, in->token));
			in = in->nx;
		}
	}
}

pid_t	fork_process(t_data *data, t_mlist *pipelines)
{
	pid_t	id;

	id = create_fork(data);
	if (id == 0)
	{
		close_extra_fds(data->pipe_fds);
		copy_pipe_fds(data, data->pipe_fds);
		if (run_builtins(data, pipelines) == false)
			execute_through_path(data, pipelines, data->path);
		exit(55);
	}
	close_main_fds(data->pipe_fds);
	return (id);
}
