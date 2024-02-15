/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/15 19:34:45 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	await_forks(t_data *data, t_mlist *pipelines, pid_t *ids, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		while (pipelines != NULL && \
		(pipelines->token != COMMAND && is_builtin(pipelines->token) == false))
			pipelines = pipelines->nx;
		wait_for_process(data, ids[i]);
		pipelines = pipelines->nx;
		i++;
	}
	free(ids);
}

static void	execute_pipelessly(t_data *data, t_mlist *pipeline)
{
	pid_t	id;

	if (run_builtins(data, pipeline) == false)
	{
		id = create_fork(data);
		if (id == 0)
		{
			if (ft_strchr(pipeline->args[0], '/') != NULL)
				execute_command(data, pipeline->args[0], pipeline->args);
			else
				execute_through_path(data, pipeline, data->path);
		}
		else
			wait_for_process(data, id);
	}
}

void	carry_out_orders(t_data *data, t_mlist *pipelines, int i)
{
	pid_t	*pids;

	if (contains_redirections(pipelines) == false)
	{
		execute_pipelessly(data, pipelines);
		return ;
	}
	pids = ft_calloc2(data, count_tokens(pipelines, PIPE) + 1, sizeof(pid_t));
	while (pipelines != NULL)
	{
		if (pipelines->pv == NULL || pipelines->token == PIPE)
		{
			pids[i] = fork_process(data, pipelines);
			if (pids[i] == -1)
				break ;
			i++;
		}
		pipelines = pipelines->nx;
	}
	await_forks(data, data->pipelines, pids, i);
}

void	build_pipelines(t_data *data, t_mlist *in, t_mlist **pipelines)
{
	char	**arr;

	while (in != NULL)
	{
		arr = list_to_array(data, in);
		if (arr != NULL)
			node_addback(pipelines, new_node(data, NULL, arr, in->token));
		while (in != NULL && is_redirection(in->token) == false)
			in = in->nx;
		if (in != NULL)
		{
			node_addback(pipelines, copy_node(data, in));
			in = in->nx;
		}
	}
}
