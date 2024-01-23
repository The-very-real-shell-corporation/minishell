/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:06:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/23 16:18:14 by vvan-der      ########   odam.nl         */
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

static void	get_path_ready(t_data *data)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	path = ft_strdup2(data, "PATH");
	tmp = envp_string(data, path);
	free(path);
	data->path = ft_split(tmp, ':');
	if (data->path == NULL)
	{
		free(tmp);
		exit_error(data, "Split error");
	}
	free(tmp);
	data->real_path = ft_calloc2(data, ptr_array_size((void **)data->path) \
						+ 1, sizeof(char *));
	while (data->path[i] != NULL)
	{
		data->real_path[i] = ft_strjoin2(data, data->path[i], "/");
		i++;
	}
}

void	initialize_data(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	assign_function_ptrs(data);
	copy_environment(data, envp);
}

void	get_input_and_parse(t_data *data)
{
	char	*line;

	line = readline("WE SHELL SEE: ");
	if (line == NULL)
		exit_builtin(data, NULL);
	if (everythingiswhitespace(line) == true)
		return ;
	add_history(line);
	get_path_ready(data);
	expansion_pack(data, line);
	free(line);
	build_pipelines(data, data->input, &data->pipelines);
}
