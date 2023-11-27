/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/27 16:39:07 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_data *data, char *path)
{
	int	exit_status;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		exit_error(data, "getcwd failed");
	exit_status = chdir(path);
	if (exit_status == -1)
	{
		free(tmp);
		printf("Error: \"%s\" is not a directory\n", path);
		return (126);
	}
	change_env_var(data, "OLDPWD=", tmp);
	change_env_var(data, "PWD=", getcwd(NULL, 0));
	// change_env_var(data, ft_strdup2(data, "OLDPWD="), tmp);
	// change_env_var(data, ft_strdup2(data, "PWD="), getcwd(NULL, 0));
	return (0);
}

int	echo_builtin(char *msg, bool n_flag)
{
	if (msg == NULL)
		return (1);
	if (n_flag == false)
		printf("%s\n", msg);
	else
		printf("%s", msg);
	return (0);
}

int	env_builtin(t_data *data)
{
	if (print_env(data->env) == -1)
		exit_error(data, "env failed to print");
	return (0);
}

int	exit_builtin(t_data *data, char *msg)
{
	if (msg == NULL)
	{
		clean_up(data);
		exit(0);
	}
	return (0);
}

int	export_builtin(t_data *data, char *input)
{
	t_mlist	*tmp;
	char	*env_string;

	if (input == NULL || *input == '\0')
	{
		clear_mlist(&data->sorted_env);
		sort_environment(data);
		print_list(data->sorted_env);
		return (0);
	}
	env_string = input;
	dollar_in_env(data, input, &env_string);
	if (env_string == NULL)
		return (printf("Error: could not add \"%s\" to environment\n", input), 1);
	tmp = find_input(data->env, env_string);
	if (tmp == NULL)
		node_addback(&data->env, new_node(data, env_string));
	else
		replace_node(data, tmp, env_string);
	data->env = node_first(data->env);
	return (0);
}
