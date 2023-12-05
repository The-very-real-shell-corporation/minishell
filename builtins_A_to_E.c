/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/05 21:26:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_data *data, char **args)
{
	int		exit_status;
	char	*tmp;

	if (*(args + 1) != NULL)
		return (-1);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		exit_error(data, "getcwd failed");
	exit_status = chdir(*args);
	if (exit_status == -1)
	{
		free(tmp);
		printf("Error: \"%s\" is not a directory\n", *args);
		return (126);
	}
	change_env_var(data, "OLDPWD=", tmp);
	change_env_var(data, "PWD=", getcwd(NULL, 0));
	return (0);
}

int	echo_builtin(t_data *data, char **args)
{
	(void)data;
	// check for "-n"
	if (*args == NULL)
		return (-1);
	while (*args != NULL)
	{
		printf("%s", *args);
		if (*(args + 1) != NULL)
			printf(" ");
		args++;
	}
	// if (n_flag == false)
	// 	printf("\n");
	return (0);
}

int	env_builtin(t_data *data, char **args)
{
	(void)args;
	if (print_env(data->env) == -1)
		exit_error(data, "env failed to print");
	return (0);
}

int	exit_builtin(t_data *data, char **args)
{
	if (*args == NULL)
	{
		clean_up(data);
		exit(0);
	}
	return (0);
}

int	export_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;
	char	*env_string;

	if (*args == NULL || **args == '\0')
	{
		printf("pointer: %p\n", data->sorted_env);
		sort_environment(data);
		printf("pointer (2): %p\n", data->sorted_env);
		print_list(data->sorted_env);
		clear_mlist(&data->sorted_env);
		printf("pointer (3): %p\n", data->sorted_env);
		return (0);
	}
	while (*args != NULL)
	{
		env_string = *args;
		dollar_in_env(data, *args, &env_string);
		if (env_string == NULL)
			printf("Error: could not add \"%s\" to environment\n", *args);
		tmp = find_input(data->env, env_string);
		if (tmp == NULL)
			node_addback(&data->env, new_node(data, env_string));
		else
			replace_node(data, tmp, env_string);
		data->env = node_first(data->env);
		args++;
	}
	return (0);
}
