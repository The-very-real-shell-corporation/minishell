/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/21 14:42:47 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	**create_pipe_fds(t_data *data, size_t n)
{
	int		**fds;
	size_t	i;

	i = 0;
	fds = ft_calloc(n + 1, sizeof(int*));
	if (fds == NULL)
		exit_error(data, "malloc failed");
	while (fds != NULL)
	{
		fds[i] = ft_calloc(2, sizeof(int));
		i++;
	}
	data->pipe_fds = fds;
}

void	create_pipes(t_data *data, int **pipe_fds)
{
	while (pipe_fds != NULL)
	{
		if (pipe(*pipe_fds) == -1)
			exit_error(data, "pipe failed to pipe");
		pipe_fds++;
	}
}

void	pipe_input(t_data *data, int func)
{
	pid_t	id1;
	pid_t	id2;
	int		fd[2];

	(void)func;
	create_pipe(data, fd);
	id1 = create_fork(data);
	set_pipes(data, id1, fd, STDOUT_FILENO, 1);
	id2 = create_fork(data);
	set_pipes(data, id2, fd, STDIN_FILENO, 0);
	wait_for_process(data, id1);
	wait_for_process(data, id2);
}