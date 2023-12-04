/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:06:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/04 18:21:43 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_data(t_data *data, char **envp)
{
	data->exit_status = 0;
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->env = NULL;
	data->sorted_env = NULL;
	copy_environment(data, envp);
}

void	parse_input(t_data *data, char *input)
{
	get_path_ready(data);
	if (everythingiswhitespace(input) == true)
		data->input = NULL;
	else
		expansion_pack(data, input);
	if (data->input == NULL)
		return ;
	data->argv = list_to_array(data, data->input);
	print_2d_charray(data->argv);
}
