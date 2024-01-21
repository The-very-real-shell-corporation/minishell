/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 19:14:53 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_through_path(t_data *data, t_mlist *p, char **path)
{
	int		i;
	char	*directory;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit_error(data, "cwd failed");
	data->env_array = list_to_array(data, data->env);
	while (path[i] != NULL)
	{
		chdir(path[i]);
		if (access(data->args[0], X_OK) == 0)
		{
			directory = ft_strjoin2(data, data->real_path[i], p->pipeline[0]);
			chdir(cwd);
			execute_command(data, directory, p->pipeline);
		}
		i++;
	}
	chdir(cwd);
	if (access(data->args[0], X_OK) == 0)
		execute_command(data, ft_strdup2(data, p->pipeline[0]), p->pipeline);
	exit(54); // look up a smart exit status
}

static bool	try_pipeless(t_data *data, t_mlist *pipeline)
{
	if (pipeline->nx == NULL)
	{
		if (run_builtins(data, pipeline) == false)
			execute_the_path(data);
		return (true);
	}
	return (false);
}


void	execute(t_data *data, t_mlist *pipelines, pid_t *pids)
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

/* void	execute(t_data *data, t_mlist *input, pid_t	*pids)
{
	int	i;

	i = 0;
	pids = ft_calloc2(data, list_size(input, DUMMY), sizeof(pid_t));
	while (input != NULL)
	{

	}
	while (i > 0)
	{
		i--;
		wait_for_process(data, pids[i]);
		printf("exit status: %d\n", data->exit_status);
	}
}
 */