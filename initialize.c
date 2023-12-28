/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:06:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/27 16:54:25 by lotse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_function_ptrs(t_data *data)
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
	data->exit_status = 0;
	data->heredocs = 0;
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->env = NULL;
	data->sorted_env = NULL;
	data->pipelines = NULL;
	data->pipe_fds = NULL;
	data->pids = NULL;
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
	data->argv = list_to_array(data, data->input);
	list_to_array_for_pip(data, data->input, &data->pipelines);
	// print_list(data->input);
	// print_2d_charray(data->argv);
}
