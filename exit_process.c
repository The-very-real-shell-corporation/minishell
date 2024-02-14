/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/14 14:28:02 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/14 16:13:47 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static bool	wexit_status(int *status, char *input)
// {
// 	if (WEXITSTATUS(*status) == EXIT_FAILURE)
// 	{
// 		ft_putstr_fd("command not found: ", STDERR_FILENO);
// 		ft_putendl_fd(input, STDERR_FILENO);
// 		return (true);
// 	}
// 	else if (WEXITSTATUS(*status) == 127)
// 	{
// 		ft_putendl_fd("error: insufficient permissions", STDERR_FILENO);
// 		return (true);
// 	}
// 	return (false);
// }

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
	// if (wexit_status(&data->exit_status, input) == true)
	// 	return ;
}
