/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 18:33:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/21 18:33:36 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, char *directory, char **args)
{
	if (execve(directory, args, data->env_array) == -1)
		exit_error(data, "execve failed");
	free(directory);
	clean_up(data);
	exit(EXIT_FAILURE); // look up a smart exit status
}

bool	run_builtins(t_data *data, t_mlist *p)
{
	if (is_builtin(p->token) == true)
	{
		data->fn[p->token](data, &p->pipeline[1]);
		return (true);
	}
	return (false);
}
