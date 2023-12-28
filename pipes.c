/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/28 14:28:45 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*new_node_pipeline(t_data *data, char **args, t_token tolkien)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (new == NULL)
		exit_error(data, "List malloc failed");
	new->pipeline = args; // make sure everything is allocated before it gets in new_node
	new->str = NULL;
	new->token = tolkien;
	new->nx = NULL;
	new->pv = NULL;
	return (new);
}

// Get the pipeline size and keep track of the position
size_t	pipeline_size(t_mlist *input)
{
	size_t	i;

	i = 0;
	while (input != NULL && (input)->token != PIPE) 
	{
		i++;
		input = (input)->nx;
	}
	return (i);
}

void	list_to_array_for_pip(t_data *data ,t_mlist *input, t_mlist **pipelines)
{
	t_mlist	*pip;
	char 	**result;
	char	*tmp;
	size_t	i;
	t_token	tolkien;

	pip = NULL; // use as tmp
	while (input != NULL)
	{
		printf("input->str: %s\n", input->str);
		result = ft_calloc((pipeline_size(input) + 1), sizeof(char *));
		if (result == NULL)
			exit_error(data, "malloc failed");
		i = 0;
		while (input != NULL)
		{
			if (input->token == PIPE)
			{
				input = input->nx;
				break ;
			}
			if (i == 0)
				tolkien = input->token;
			result[i] = ft_strdup2(data, input->str);
			tmp = result[i];
			result[i] = ft_strtrim(tmp, " "); 
			free(tmp);
			input = input->nx;
			i++;
		}
		node_addback(&pip, new_node_pipeline(data, result, tolkien));
		print_2d_charray(result);
	}
	*pipelines = pip;
}

void	create_pipe_fds(t_data *data, size_t n)
{
	int		**fds;
	size_t	i;

	i = 0;
	fds = ft_calloc(n + 1, sizeof(int*));
	if (fds == NULL)
		exit_error(data, "malloc failed");
	while (i < n)
	{
		fds[i] = ft_calloc(2, sizeof(int));
		if (fds[i] == NULL)
			exit_error(data, "malloc failed");
		i++;
	}
	data->pipe_fds = fds;
}

void	create_pipes(t_data *data, int **pipe_fds)
{	int i = 0;	
	while (pipe_fds[i] != NULL)
	{
		if (pipe(pipe_fds[i]) == -1)
			exit_error(data, "pipe failed to pipe");
		i++;
	}
}

void	set_pipes(t_data *data, pid_t id, int fd[], int pipe_fd, int x)
{
	if (id == 0)
	{
		if (dup2(fd[x], pipe_fd) == -1)
			exit_error(data, "dup2 failed");
		close(fd[0]);
		close(fd[1]);
		// go do something
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
}

bool	run_builtins_pip(t_data *data, t_mlist *pipelines)
{
	t_token	token;

	token = pipelines->token;
	if (token <= 6)
	{
		write(STDOUT_FILENO, "HEYAAAA\n", 9);
		data->fn[token](data, pipelines->pipeline);
		return (true);
	}
	return (false);		
}

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
			directory = ft_strjoin(data->real_path[i], pipelines->pipeline[0]);
			chdir(data->cwd);
			execute_command(data, directory);
		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup(pipelines->pipeline[0]));
	// exit(EXIT_FAILURE); // look up a smart exit status
}

pid_t	create_fork_pip(t_data *data)
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

void	fork_stuff_pip(t_data *data, t_mlist *pipelines, pid_t *pids, size_t n)
{
	t_mlist	*tmp;
	size_t	i;

	tmp = pipelines;
	i = 0;
	pids = ft_calloc(n + 1, sizeof(pid_t));
	if (pids == NULL)
		exit_error(data, "malloc failed");
	while (i < n)
	{
		pids[i] = create_fork(data);
		if (pids[i] == 0)
			break ;
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pids[i] == 0)
			search_the_path_pip(data, pipelines, data->path);
		i++;
		pipelines = pipelines->nx;
	}
	pipelines = tmp;
	i = 0;
	while (i < n)
	{
		wait_for_process(data, pids[i]);
		i++;
	}
}

// Modify this one
// void	set_pipes(t_data *data, pid_t id,)
// {
// 	if (id == 0)
// 	{
// 		if (dup2(fd[x], pipe_fd) == -1)
// 			exit_error(data, "dup2 failed");
// 		close(fd[0]);
// 		close(fd[1]);
// 		// go do something
// 		exit(0);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// }

// void	pipe_input(t_data *data, int func)
// {
// 	pid_t	id1;
// 	pid_t	id2;
// 	int		fd[2];

// 	(void)func;
// 	create_pipes(data, fd);
// 	id1 = create_fork(data);
// 	set_pipes(data, id1, fd, STDOUT_FILENO, 1);
// 	id2 = create_fork(data);
// 	set_pipes(data, id2, fd, STDIN_FILENO, 0);
// 	wait_for_process(data, id1);
// 	wait_for_process(data, id2);
// }