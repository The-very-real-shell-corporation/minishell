/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/02 18:44:35 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data, char **args)
{
	if (args != NULL && *args != NULL)
	{
		ft_putendl_fd("cannot run env with argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (print_env(data->env) == -1)
		ft_putendl_fd("environment is empty", STDOUT_FILENO);
	return (0);
}