/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:31 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/14 14:20:48 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_check(char **args)
{
	while (*args != NULL)
	{
		if (**args == '\0')
		{
			ft_putendl_fd("error: empty string in export", STDERR_FILENO);
			return (ERROR);
		}
		if (ft_isalpha(**args) == false && **args != '_')
		{
			ft_putstr_fd("error: export must start with ", STDERR_FILENO);
			ft_putendl_fd("a letter or underscore", STDERR_FILENO);
			return (ERROR);
		}
		args++;
	}
	return (SUCCESS);
}

static bool	with_arguments(t_data *data, char **args)
{
	char	*env_string;
	t_mlist	*tmp;

	while (*args != NULL)
	{
		env_string = *args;
		dollar_in_env(data, *args, &env_string);
		if (env_string == NULL)
		{
			printf("Error: could not add \"%s\" to environment\n", *args); // -> std error
			return (ERROR);
		}
		tmp = find_input(data->env, env_string);
		if (tmp == NULL)
			node_addback(&data->env, \
			new_node(data, ft_strdup2(data, env_string), NULL, INIT));
		else
			replace_node(data, tmp, env_string);
		data->env = node_first(data->env);
		args++;
	}
	return (SUCCESS);
}

int	export_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;

	if (error_check(args) == ERROR)
		return (ERROR);
	if (*args == NULL)
	{
		tmp = sort_environment(data, node_first(data->env));
		print_list(node_first(tmp));
		return (clear_mlist(&tmp), SUCCESS);
	}
	if (with_arguments(data, args) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
