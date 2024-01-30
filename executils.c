/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 18:33:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/30 14:43:16 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *directory, char **args)
{
	if (execve(directory, args, data->env_array) == -1)
		exit_error(data, "execve failed");
	free(directory);
	clean_up(data);
	exit(EXIT_FAILURE);
}

bool	run_builtins(t_data *data, t_mlist *pipeline)
{
	if (is_builtin(pipeline->token) == true)
	{
		data->fn[pipeline->token](data, &pipeline->args[1]);
		return (true);
	}
	return (false);
}
