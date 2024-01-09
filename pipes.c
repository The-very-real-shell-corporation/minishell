/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/09 17:50:07 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_pipeline(t_data *data, t_mlist *input, t_token tolkien)
{
	char 	**result;
	char	*tmp;
	size_t	i;

	result = ft_calloc((pipeline_size(input) + 1), sizeof(char *));
	if (result == NULL)
		exit_error(data, "malloc failed");
	i = 0;
	while (input != NULL && input->token != PIPE)
	{
		result[i] = ft_strdup2(data, input->str);
		tmp = result[i];
		result[i] = ft_strtrim(tmp, " ");
		free(tmp);
		input = input->nx;
		i++;
	}
	while (input != NULL && input->token == PIPE)
		input = input->nx;
	node_addback(&data->pipelines, new_node(data, NULL, result, tolkien));
	if (input != NULL)
		build_pipeline(data, input, input->token);
}

bool	run_builtins_pip(t_data *data, t_mlist *pipelines)
{
	t_token	token;

	token = pipelines->token;
	if (token <= 6)
	{
		// write(STDOUT_FILENO, "Pippin\n", 8);
		data->fn[token](data, &pipelines->pipeline[1]);
		return (true);
	}
	return (false);
}

/* void	search_the_path_pip(t_data *data, t_mlist *pipelines, char **path)
{
	int		i;
	char	*directory;

	i = 0;
	int id = fork();
	if (id == 0)
	{
		data->env_array = list_to_array(data, data->env);
		while (path[i] != NULL)
		{
			chdir(path[i]);
			if (access(data->argv[0], X_OK) == 0)
			{
				directory = ft_strjoin2(data, data->real_path[i], pipelines->pipeline[0]);
				chdir(data->cwd);
				execute_command(data, directory, pipelines->pipeline);
			}
			i++;
		}
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup(pipelines->pipeline[0]), pipelines->pipeline);
	// exit(EXIT_FAILURE); // look up a smart exit status
} */

void	search_the_path_pip(t_data *data, t_mlist *pipelines, char **path)
{
	int		i;
	char	*directory;

	i = 0;
	data->env_array = list_to_array(data, data->env);
	while (path[i] != NULL)
	{
		chdir(path[i]);
		if (access(data->argv[0], X_OK) == 0)
		{
			directory = ft_strjoin2(data, data->real_path[i], pipelines->pipeline[0]);
			chdir(data->cwd);
			execute_command(data, directory, pipelines->pipeline);
		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup(pipelines->pipeline[0]), pipelines->pipeline);
	exit(54); // look up a smart exit status
}

void	close_extra_fds(int **pipe_fds, int pos, int total_pipes)
{
	int	pipe_num;

	pipe_num = 0;
	while (pipe_num < total_pipes)
	{
		if (pipe_num != pos - 1)
			close(pipe_fds[pipe_num][0]);
		if (pipe_num != pos)
			close(pipe_fds[pipe_num][1]);
		pipe_num++;
	}
}

void	copy_pipe_fds(t_data *data, int **pipe_fds, int pos, int pipes)
{
	if (pos > 0)
	{
		if (dup2(pipe_fds[pos - 1][0], STDIN_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[pos - 1][0]);
	}
	if (pos < pipes)
	{
		if (dup2(data->pipe_fds[pos][1], STDOUT_FILENO) == -1)
			exit_error(data, "dup2 failed");
		close(data->pipe_fds[pos][1]);
	}
}

void	fork_stuff_pip(t_data *data, t_mlist *pipelines, pid_t *pids, int pipes)
{
	int		i;

	i = 0;
	pids = ft_calloc(pipes + 1, sizeof(pid_t));
	if (pids == NULL)
		exit_error(data, "malloc failed");
	while (i < pipes + 1)
	{
		pids[i] = create_fork(data);
		if (pids[i] == 0)
		{
			// free(pids);
			close_extra_fds(data->pipe_fds, i, pipes);
			copy_pipe_fds(data, data->pipe_fds, i, pipes);
			if (run_builtins_pip(data, pipelines) == false)
				search_the_path_pip(data, pipelines, data->path);
			exit(55);
		}
		i++;
		pipelines = pipelines->nx;
	}
	close_pipes(data->pipe_fds);
	while (i > 0)
	{
		i--;
		wait_for_process(data, pids[i]);
		printf("Exit status: %d\n", data->exit_status);
	}
}
