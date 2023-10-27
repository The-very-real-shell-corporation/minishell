/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/27 17:25:13 by akasiota      ########   odam.nl         */
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

void	exit_builtin(char *msg)
{
	if (msg == NULL)
		exit(0);
}

void	export_builtin(t_data *data, char *input)
{
	t_mlist	*tmp;

	sort_environment(data); /* added this line here to work with sorted list in case of NULL input */ 
	if (input == NULL)
	{
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
