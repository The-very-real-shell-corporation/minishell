/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:20:13 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/22 15:10:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_process(t_data *data, pid_t id, char *input)
{
	waitpid(id, &data->exit_status, 0);
	if (WEXITSTATUS(data->exit_status) == EXIT_FAILURE)
	{
		write(STDERR_FILENO, input, ft_strlen(input));
		write(STDERR_FILENO, ": command not found\n", 21);
		return ;
	}
	if (WEXITSTATUS(data->exit_status) == EXEC_ERR)
	{
		write(STDERR_FILENO, input, ft_strlen(input));
		write(STDERR_FILENO, ": could not execute\n", 21);
		return ;
	}
	if (WIFSIGNALED(data->exit_status) != 0)
	{
		if (WTERMSIG(data->exit_status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		}	
		else if (WTERMSIG(data->exit_status) == SIGQUIT)
		{	
			write(STDOUT_FILENO, "My core dumped, ouchie\n", 23);
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		}
	}
	else
	{
		data->exit_status = WEXITSTATUS(data->exit_status);	
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
