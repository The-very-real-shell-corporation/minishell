/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/15 20:14:57 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_builtin(char *path)
{
	if (chdir(path) == -1)
		printf("Error: \"%s\" is not a directory\n", path);
}

void	echo_builtin(char *msg, bool n_flag)
{
	if (n_flag == false)
		printf("%s\n", msg);
	else
		printf("%s", msg);
}

void	env_builtin(t_data *data)
{
	print_env(data->env);
}

void	exit_builtin(t_data *data, char *msg)
{
	if (msg == NULL)
	{
		clean_up(data);
		exit(0);
	}
}

void	export_builtin(t_data *data, char *input)
{
	t_mlist	*tmp;

	if (input == NULL)
	{
		sort_environment(data);
		print_list(data->sorted_env);
		return ;
	}
	tmp = find_input(data->env, input);
	if (tmp == NULL)
		node_addback(&data->env, new_node(data, input));
	else
		replace_node(data, tmp, input);
	sort_environment(data);
	data->env = node_first(data->env);
}
