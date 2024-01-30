/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:20:13 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 14:51:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_process(t_data *data, pid_t id, char *input)
{
	waitpid(id, &data->exit_status, 0);
	if (WEXITSTATUS(data->exit_status) == EXIT_FAILURE)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(input, STDERR_FILENO);
		return ;
	}
	if (WEXITSTATUS(data->exit_status) == EXEC_ERR)
	{
		write(STDERR_FILENO, input, ft_strlen(input));
		write(STDERR_FILENO, ": could not execute\n", 21);
		return ;
	}
	return ;
	if (WIFSIGNALED(data->exit_status) != 0)
	{
		if (WTERMSIG(data->exit_status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		}
		else if (WTERMSIG(data->exit_status) == SIGQUIT)
		{
			write(STDERR_FILENO, "My core dumped, ouchie\n", 23);
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		}
	}
	else if (WEXITSTATUS(data->exit_status) != 0)
	{
		write(STDERR_FILENO, "Not sure what but something went wrong\n", 40);
	}
}

pid_t	create_fork(t_data *data)
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

void	execute_the_path(t_data *data)
{
	pid_t	id;

	id = create_fork(data);
	if (id == 0)
		execute_through_path(data, data->pipelines, data->path);
	wait_for_process(data, id, data->pipelines->args[0]);
}

pid_t	fork_process(t_data *data, t_mlist *pipeline, int direction)
{
	pid_t	id;

	setup_redirection(data, pipeline);
	id = create_fork(data);
	if (id == 0)
	{
		if (direction == LEFT)
			direct_pipes_left(data, data->pipe_fds);
		if (direction == RIGHT)
			direct_pipes_right(data, data->pipe_fds);
		if (pipeline->token == FILENAME || pipeline->token == RE_INPUT)
		{
			clean_up(data);
			exit(EXIT_SUCCESS);
		}
		if (run_builtins(data, pipeline) == false)
			execute_through_path(data, pipeline, data->path);
		clean_up(data);
		exit(EXIT_SUCCESS);
	}
	close_main_fds(data->pipe_fds);
	return (id);
}
