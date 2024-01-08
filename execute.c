/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/08 18:17:20 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *directory, char **args)
{
	execve(directory, args, data->env_array);
	free(directory);
	clean_up(data);
	exit(EXIT_FAILURE); // look up a smart exit status
}

bool	run_builtins(t_data *data)
{
	t_token	token;

	token = data->input->token;
	if (token <= 6)
	{
		write(STDOUT_FILENO, "HEYAAAA\n", 9);
		data->fn[token](data, &data->argv[1]);
		return (true);
	}
	return (false);		
}

void	execute_pip(t_data *data, t_mlist *pipelines, pid_t	*pids)
{
	int	pipes;

	pipes = (int)list_size(pipelines) - 1;
	// printf("n: %zu\n", pipes);
	if (pipes > 0)
	{
		create_pipe_fds(data, pipes);
		open_pipes(data, data->pipe_fds);
		fork_stuff_pip(data, pipelines, pids, pipes);
		close_pipes(data->pipe_fds);
	}
	else if (run_builtins_pip(data, pipelines) == false)
	{
		puts("elif\n");
		fork_stuff(data);
	}
}

/* void	execute(t_data *data)
{
	// pid_t	id;

	// if (data->input->token = stuff)
	// 	data->input = data->input->nx;
	if (run_builtins(data) == false)
		fork_stuff(data);
} */
