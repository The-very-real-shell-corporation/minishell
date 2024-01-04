/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/04 20:38:56 by akasiota      ########   odam.nl         */
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
size_t	pipelines_size(t_mlist *input)
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
		// printf("input->str: %s\n", input->str);
		result = ft_calloc((pipelines_size(input) + 1), sizeof(char *));
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

void	open_pipes(t_data *data, int **pipe_fds)
{	int i = 0;	
	while (pipe_fds[i] != NULL)
	{
		if (pipe(pipe_fds[i]) == -1)
			exit_error(data, "pipe failed to pipe");
		i++;
	}
}

void	close_pipes(int **pipe_fds)
{
	int	i = 0;
	while (pipe_fds[i] != NULL)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

// void	set_pipes(t_data *data, pid_t id, int fd[], int pipe_fd, int x)
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

bool	run_builtins_pip(t_data *data, t_mlist *pipelines)
{
	t_token	token;

	token = pipelines->token;
	if (token <= 6)
	{
		write(STDOUT_FILENO, "HEYAAAA\n", 9);
		data->fn[token](data, &pipelines->pipeline[1]);
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
			execute_command(data, directory, pipelines->pipeline);
			puts("here!");

		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup(pipelines->pipeline[0]), pipelines->pipeline);
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
	size_t	j;

	tmp = pipelines;
	i = 0;
	pids = ft_calloc(n + 1, sizeof(pid_t));
	if (pids == NULL)
		exit_error(data, "malloc failed");
	while (i < n)
	{
		j = 0;
		pids[i] = create_fork(data);
		if (pids[i] == 0)
		{
			while (j < n - 1)
			{
				if (j != i - 1) // change to int counters? It doesn't seem to matter
				{
					// printf("before: closing %zu[0]\n", j);
					close(data->pipe_fds[j][0]);
				}
				if (j != i)
				{
					// printf("before: closing %zu[1]\n", j);
					close(data->pipe_fds[j][1]);
				}
				j++;
			}
			if (i > 0)
			{
				if (dup2(data->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
					exit_error(data, "dup2 failed");
				// printf("after: closing %zu[0]\n", i - 1);
				close(data->pipe_fds[i - 1][0]);
			}
			if (i < n - 1)
			{
				if (dup2(data->pipe_fds[i][1], STDOUT_FILENO) == -1)
					exit_error(data, "dup2 failed");
				// printf("after: closing %zu[1]\n", i);
				close(data->pipe_fds[i][1]);
			}
			if (run_builtins_pip(data, pipelines) == false)
				search_the_path_pip(data, pipelines, data->path);
			return ;
		}
		i++;
		pipelines = pipelines->nx;
	}
	i = 0;
	pipelines = tmp;
	while (i < n)
	{
		wait_for_process(data, pids[i]);
		i++;
	}
}

void print_open_fds() {
    int fd;
    for (fd = 0; fd < FD_SETSIZE; fd++) {
        if (fcntl(fd, F_GETFD) != -1 || errno != EBADF) {
            printf("File descriptor %d is open.\n", fd);
        }
    }
}