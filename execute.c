/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 21:00:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	try_pipeless(t_data *data, t_mlist *pipeline)
{
	if (pipeline->nx == NULL)
	{
		if (run_builtins(data, pipeline) == false)
			fork_stuff(data);
		return (true);
	}
	return (false);
}

void	execute_command(t_data *data, char *directory, char **args)
{
	if (execve(directory, args, data->env_array) == -1)
		exit_error(data, "execve failed");
	free(directory);
	clean_up(data);
	exit(EXIT_FAILURE); // look up a smart exit status
}

bool	run_builtins(t_data *data, t_mlist *p)
{
	if (p->token <= 6)
	{
		data->fn[p->token](data, &p->pipeline[1]);
		return (true);
	}
	return (false);
}

void	execute(t_data *data, t_mlist *pipelines, pid_t	*pids)
{
	int	i;

	i = 0;
	if (try_pipeless(data, pipelines) == true)
		return ;
	pids = ft_calloc2(data, list_size(pipelines, DUMMY), sizeof(pid_t));
	while (pipelines != NULL)
	{
		if (pipelines->pv == NULL)
			open_pipe(data, 0);
		else if (pipelines->nx == NULL)
			open_pipe(data, 1);
		else
			open_pipe(data, 2);
		pids[i] = fork_pipe(data, pipelines);
		close_main_fds(data->pipe_fds);
		i++;
		pipelines = pipelines->nx;
	}
	while (i > 0)
	{
		i--;
		wait_for_process(data, pids[i]);
		printf("exit status: %d\n", data->exit_status);
	}
}
