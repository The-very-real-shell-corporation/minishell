/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/21 20:41:23 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *directory)
{
	execve(directory, data->argv, data->env_array);
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

bool	run_builtins_pip(t_data *data, t_mlist *pipelines)
{
	t_token	token;

	token = pipelines->token;
	if (token <= 6)
	{
		write(STDOUT_FILENO, "HEYAAAA\n", 9);
		data->fn[token](data, &data->argv[1]);
		return (true);
	}
	return (false);		
}


void	execute(t_data *data, t_mlist *pipelines, pid_t	*pids)
{
	size_t	n;
	size_t	i;

	// if (data->input->token = stuff)
	// 	data->input = data->input->nx;
	i = 0;
	n = list_size(pipelines);
	while (pipelines != NULL)
	{
		if (n > 1)
		{
			create_pipe_fds(data, n);
			create_pipes(data, data->pipe_fds);
			fork_stuff_pip(data, pipelines, data->pids, n);
			while (i < n)
			{
				
			}
		}
		if (run_builtins(data) == false)
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
