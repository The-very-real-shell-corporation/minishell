/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:20:13 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/07 16:43:23 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_process(t_data *data, pid_t id, char *input)
{
	0x7f;
	waitpid(id, &data->exit_status, 0);
	if (WIFSIGNALED(data->exit_status) != 0)
	{
		if (WTERMSIG(data->exit_status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		}
		else if (WTERMSIG(data->exit_status) == SIGQUIT)
		{
			ft_putendl_fd("My core dumped, ouchie.", STDERR_FILENO);
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		}
	}
	else if (WEXITSTATUS(data->exit_status) == EXIT_FAILURE)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(input, STDERR_FILENO);
	}
	// else if (WEXITSTATUS(data->exit_status) == EXEC_ERR)
	// {
	// 	ft_putstr_fd(input, STDERR_FILENO);
	// 	ft_putendl_fd(": could not execute\n", STDERR_FILENO);
	// }
	else if (WEXITSTATUS(data->exit_status) != 0)
	{
		ft_putendl_fd("Not sure what but something went wrong", STDERR_FILENO);
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

pid_t	fork_process(t_data *data, t_mlist *pipeline)
{
	pid_t	id;

	if (pipeline->pv == NULL && count_tokens(pipeline, PIPE) != 0)
		open_pipe(data, START);
	else if (count_tokens(pipeline->nx, PIPE) != 0)
		open_pipe(data, MIDDLE);
	else
		open_pipe(data, END);
	id = create_fork(data);
	if (id == 0)
	{
		if (pipeline->token == PIPE)
			pipeline = pipeline->nx;
		if (setup_redirections(data, pipeline) == ERROR)
			return (-1);
		make_pipes_pipe(data, data->pipe_fds);
		if (run_builtins(data, pipeline) == false)
			execute_through_path(data, pipeline, data->path);
		clean_up(data);
		exit(EXIT_SUCCESS);
	}
	close_main_fds(data->pipe_fds);
	return (id);
}
