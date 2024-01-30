/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:31 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 18:43:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;
	char	*env_string;

	if (*args == NULL || **args == '\0')
	{
		tmp = sort_environment(data, node_first(data->env));
		print_list(node_first(tmp));
		return (clear_mlist(&tmp), 0);
	}
	while (*args != NULL)
	{
		env_string = *args;
		dollar_in_env(data, *args, &env_string);
		if (env_string == NULL)
			printf("Error: could not add \"%s\" to environment\n", *args);
		tmp = find_input(data->env, env_string);
		if (tmp == NULL)
			node_addback(&data->env, \
			new_node(data, ft_strdup2(data, env_string), NULL, INITIALIZED));
		else
			replace_node(data, tmp, env_string);
		data->env = node_first(data->env);
		args++;
	}
	return (0);
}