/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 19:10:02 by vincent       ########   odam.nl         */
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

void	build_pipeline(t_data *data, t_mlist *in, t_mlist **pipelines)
{
	char 	**arr;

	print_list(in);
	arr = list_to_array(data, in);
	if (arr != NULL)
		node_addback(pipelines, new_node(data, NULL, arr, in->token));
	while (in != NULL && is_redirection(in->token) == false)
		in = in->nx;
	if (in != NULL)
		build_pipeline(data, in->nx, pipelines + 1);
	if (in != NULL && is_redirection(in->token) == true) // recursion is funny, but this can be first too
		node_addback(pipelines, new_node(data, NULL, NULL, in->token));
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
			execute_through_path(data, pipelines, data->path);
		exit(55);
	}
	close_main_fds(data->pipe_fds);
	return (id);
}
