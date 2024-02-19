/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 18:22:38 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;

	if (*args == NULL)
	{
		ft_putendl_fd("Please provide a variable to unset", STDERR_FILENO);
		return (EXIT_SUCCESS);
	}
	while (*args != NULL)
	{
		if (ft_strchr(*args, '=') == NULL)
		{
			tmp = find_input(data->env, *args);
			if (tmp != NULL)
				unlink_node(tmp);
		}
		args++;
	}
	return (EXIT_SUCCESS);
}
