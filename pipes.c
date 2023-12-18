/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/18 17:35:05 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo "hi what" | wc -l

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

void	create_pipe(t_data *data, int fd[])
{
	if (pipe(fd) == -1)
		exit_error(data, "pipe failed to pipe");
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