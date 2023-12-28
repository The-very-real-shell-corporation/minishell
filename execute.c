/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 15:44:07 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/28 14:21:22 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *directory)
{
	execve(directory, data->argv, data->env_array);
	free(directory);
	clean_up(data);
	exit(EXEC_ERR); // look up a smart exit status
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
	size_t	n;

	// if (data->input->token = stuff)
	// 	data->input = data->input->nx;
	n = list_size(pipelines);
	printf("n: %zu\n", n);
	
	// while (pipelines != NULL)
	// {
		if (n > 1)
		{
			create_pipe_fds(data, n - 1);
			create_pipes(data, data->pipe_fds);
			fork_stuff_pip(data, pipelines, pids, n);
		}
		else if (run_builtins_pip(data, pipelines) == false)
		{
			puts("elif\n");
			fork_stuff(data);
		}
		// pipelines = pipelines->nx;
	// }
}

/* void	execute(t_data *data)
{
	// pid_t	id;

	// if (data->input->token = stuff)
	// 	data->input = data->input->nx;
	if (run_builtins(data) == false)
		fork_stuff(data);
} */
