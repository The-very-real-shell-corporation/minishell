/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 20:55:11 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_builtin(char *path)
{
	if (chdir(path) == -1)
		printf("Error: \"%s\" is not a directory\n", path);
}

void	echo_builtin(char *msg, char *flag)
{
	if (flag == NULL)
		printf("%s\n", msg);
	else if (ft_strncmp(flag, "-n", 2) == 0)
		printf("%s%%", msg);
}

void	env_builtin(t_data *data)
{
	print_env(data->env);
}

void	exit_builtin(char *msg)
{
	if (msg == NULL)
		exit(0);
}

void	export_builtin(t_data *data, char *input)
{
	if (input == NULL)
	{
		sort_environment(data);
		print_list(data->sorted_env);
	}
	else if (find_input(data, input) == false)
		node_addback(&data->env, new_node(data, input));
}

