/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 14:28:02 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 18:31:08 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	waifu_exit(int *status)
{
	if (WIFSIGNALED(*status) == true)
	{
		if (WTERMSIG(*status) == SIGINT)
		{
			*status = 128 + WTERMSIG(*status);
		}
		if (WTERMSIG(*status) == SIGQUIT)
		{
			ft_putendl_fd("My core dumped, ouchie.", STDERR_FILENO);
			*status = 128 + WTERMSIG(*status);
		}
		return (true);
	}
	return (false);
}

void	wait_for_process(t_data *data, pid_t id)
{
	waitpid(id, &data->exit_status, 0);
	if (waifu_exit(&data->exit_status) == true)
		return ;
	data->exit_status = data->exit_status >> 8;
}
