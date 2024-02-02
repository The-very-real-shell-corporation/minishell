/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/02 13:33:36 by vvan-der      ########   odam.nl         */
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

static bool	try_pipeless(t_data *data, t_mlist *pipeline) // needs to loop & do redirections
{
	if (pipeline == NULL)
		return (true);
	if (pipeline->nx == NULL)
	{
		if (run_builtins(data, pipeline) == false)
			execute_the_path(data);
		return (true);
	}
	return (false);
}

void	carry_out_orders(t_data *data, t_mlist *pipelines, int i)
{
	t_mlist	*tmp;

	if (try_pipeless(data, pipelines) == true)
		return ;
	open_pipe(data, START);
	data->pids = ft_calloc2(data, count_pipes(pipelines) + 1, sizeof(pid_t));
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
	while (i > 0)
	{
		i--;
		wait_for_process(data, data->pids[i], "");
	}
}
