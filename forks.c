/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 15:20:13 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/28 14:19:11 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_process(t_data *data, pid_t id)
{
	waitpid(id, &data->exit_status, 0);
	if (WEXITSTATUS(data->exit_status) == EXIT_FAILURE)
	{
		write(STDOUT_FILENO, "Couldn't find path\n", 20);
		return ;
	}
	if (WEXITSTATUS(data->exit_status) == EXEC_ERR)
	{
		write(STDOUT_FILENO, "Error: could not execute\n", 26);
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
			write(STDOUT_FILENO, "CORE DUMPED MOTHAFUCKA\n", 23);
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

void	fork_stuff(t_data *data)
{
	pid_t	id;

	id = create_fork(data);
	if (id == 0)
		search_the_path(data, data->path);
	wait_for_process(data, id);
}
