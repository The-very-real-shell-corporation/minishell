/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/05 18:43:56 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_stuff(t_data *data)
{
	pid_t	id;

	id = fork();
	if (id == 0)
	{
		signals_for_kids();
		if (search_the_path(data, data->path) == false)
			printf("Couldn't find your fucking path, moron\n");
		clean_up(data);
		exit(0);
	}
	else
	{
		unset_signals();
	}
	waitpid(id, &data->exit_status, 0);
	if (WIFSIGNALED(data->exit_status))
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

bool	run_builtins(t_data *data)
{
	t_mlist	*input;

	input = data->input;
	if (input->token <= 6)
	{
		write(STDOUT_FILENO, "HEYAAAA\n", 9);
		data->fn[input->token](data, &data->argv[1]);
		return (true);
	}
	return (false);		
}

void	execute(t_data *data)
{
	// pid_t	id;

	// if (data->input->token = stuff)
	// 	data->input = data->input->nx;
	if (run_builtins(data) == false)
		fork_stuff(data);
	
}