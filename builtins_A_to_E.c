/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/26 15:04:27 by vincent       ########   odam.nl         */
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
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		exit_error(data, "getcwd failed");
	change_env_var(data, "PWD=", tmp);
	return (0);
}

int	echo_builtin(t_data *data, char **args)
{
	bool	n_flag;

	if (*args == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	(void)data;
	n_flag = false;
	if (ft_strncmp("-n", *args, 3) == 0)
	{
		n_flag = true;
		args++;
	}
	while (*args != NULL)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1) != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		args++;
	}
	if (n_flag == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	env_builtin(t_data *data, char **args)
{
	(void)args;
	if (data->env == NULL)
		return (0);
	print_list(data->env);
	if (print_env(data->env) == -1)
		exit_error(data, "env failed to print");
	return (0);
}

int	exit_builtin(t_data *data, char **args)
{
	(void)args;
	ft_putendl_fd("exit", STDOUT_FILENO);
	clean_up(data);
	exit(EXIT_SUCCESS);
}

int	export_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;
	char	*env_string;

	if (*args == NULL || **args == '\0')
	{
		tmp = sort_environment(data, node_first(data->env));
		print_list(tmp);
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
