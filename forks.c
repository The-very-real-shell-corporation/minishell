/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:20:13 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/14 14:56:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	create_fork(t_data *data)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		exit_error(data, "fork got forked");
	if (id == 0)
		signals_for_kids();
	else
		unset_signals();
	return (id);
}

pid_t	fork_process(t_data *data, t_mlist *pipeline)
{
	pid_t	id;

	if (pipeline->pv == NULL && count_tokens(pipeline, PIPE) != 0)
		open_pipe(data, START);
	else if (count_tokens(pipeline->nx, PIPE) != 0)
		open_pipe(data, MIDDLE);
	else
		open_pipe(data, END);
	id = create_fork(data);
	if (id == 0)
	{
		if (pipeline->token == PIPE)
			pipeline = pipeline->nx;
		if (setup_redirections(data, pipeline) == ERROR)
			return (-1);
		make_pipes_pipe(data, data->pipe_fds);
		if (run_builtins(data, pipeline) == false)
			execute_through_path(data, pipeline, data->path);
		clean_up(data);
		exit(data->exit_status);
	}
	close_main_fds(data->pipe_fds);
	return (id);
}
