/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:06:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 20:11:23 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_function_ptrs(t_data *data)
{
	data->fn[B_CD] = &cd_builtin;
	data->fn[B_ECHO] = &echo_builtin;
	data->fn[B_ENV] = &env_builtin;
	data->fn[B_EXIT] = &exit_builtin;
	data->fn[B_EXPORT] = &export_builtin;
	data->fn[B_PWD] = &pwd_builtin;
	data->fn[B_UNSET] = &unset_builtin;
}

void	initialize_data(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	copy_environment(data, envp);
	assign_function_ptrs(data);
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
	data->argv = list_to_array(data, data->input, DUMMY);
	build_pipeline(data, data->input, data->input->token);
}
