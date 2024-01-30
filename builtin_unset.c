/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 18:44:26 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;

	if (*args == NULL)
	{
		printf("Please provide a variable to unset\n");
		return (0);
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
	return (0);
}
