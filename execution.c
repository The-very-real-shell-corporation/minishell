/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/06 18:25:21 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_all_forks(t_data *data, t_mlist *pipelines, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		while (pipelines != NULL && \
		(pipelines->token != COMMAND && is_builtin(pipelines->token) == false))
			pipelines = pipelines->nx;
		wait_for_process(data, data->pids[i], pipelines->args[0]);
		pipelines = pipelines->nx;
		i++;
	}
}

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
		if (access(p->args[0], X_OK) == 0)
		{
			directory = ft_strjoin2(data, data->real_path[i], p->args[0]);
			chdir(cwd);
			execute_command(data, directory, p->args);
		}
		i++;
	}
	chdir(cwd);
	if (access(p->args[0], X_OK) == 0)
		execute_command(data, ft_strdup2(data, p->args[0]), p->args);
	exit(EXIT_FAILURE);
}

static void	execute_pipelessly(t_data *data, t_mlist *pipeline)
{
	pid_t	id;

	if (run_builtins(data, pipeline) == false)
	{
		id = create_fork(data);
		if (id == 0)
			execute_through_path(data, pipeline, data->path);
		else
			wait_for_process(data, id, pipeline->args[0]);
	}
}

void	carry_out_orders(t_data *data, t_mlist *pipelines, int i)
{
	if (contains_redirections(pipelines) == false)
	{
		execute_pipelessly(data, pipelines);
		return ;
	}
	data->pids = ft_calloc2(data, count_tokens(pipelines, PIPE) + 1, sizeof(pid_t));
	while (pipelines != NULL)
	{
		if (pipelines->pv == NULL || pipelines->token == PIPE)
		{
			data->pids[i] = fork_process(data, pipelines);
			if (data->pids[i] == -1)
				break ;
			i++;
		}
		pipelines = pipelines->nx;
	}
	wait_for_all_forks(data, data->pipelines, i);
}
