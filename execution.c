/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/22 20:57:52 by vvan-der      ########   odam.nl         */
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
	exit(54); // look up a smart exit status
}

static bool	try_pipeless(t_data *data, t_mlist *pipeline)
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


/* void	execute2(t_data *data, t_mlist *pipelines, pid_t *pids)
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
		pids[i] = fork_process(data, pipelines);
		i++;
		pipelines = pipelines->nx;
	}
	while (i > 0)
	{
		i--;
		wait_for_process(data, pids[i], data->pipelines->args[0]);
		printf("exit status: %d\n", data->exit_status);
	}
} */

pid_t	execute(t_data *data, t_mlist *input)
{
	pid_t	id;

	while (input != NULL && is_redirection(input->token) == false)
	{
		if (input->token == FILENAME)
			setup_redirection(data, input);
		if (input->pv == NULL)
			open_pipe(data, 0);
		else if (input->nx == NULL)
			open_pipe(data, 1);
		else if (input->nx->token == PIPE)
			open_pipe(data, 2);
		id = fork_process(data, input);
		input = input->nx;
	}
	return (id);
}

void	carry_out_orders(t_data *data, t_mlist *pipelines, pid_t *pids)
{
	int	i;

	i = 0;
	if (try_pipeless(data, pipelines) == true)
		return ;
	pids = ft_calloc2(data, list_size(pipelines, DUMMY), sizeof(pid_t)); // make it more precisely allocate?
	while (pipelines != NULL)
	{
		pids[i] = execute(data, pipelines);
		pipelines = pipelines->nx;
		if (pipelines != NULL && is_redirection(pipelines->token) == true)
			pipelines = pipelines->nx;
		i++;
	}
	while (i > 0)
	{
		i--;
		wait_for_process(data, pids[i], "WHAT");
		printf("exit status: %d\n", data->exit_status);
	}
}
