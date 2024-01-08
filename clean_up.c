/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 18:29:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/28 13:49:09 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	unlink_files(t_data *data)
// {
// 	char	*tmp;
// }

void	free_2d_(void **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL)
	{
		free(input[i]);
		input[i] = NULL;
		i++;
	}
	// free_and_null((void *)input);
	free(input);
	input = NULL;
}

void	free_and_null(void *variable)
{
	free(variable);
	variable = NULL;
}

void	clean_up(t_data *data)
{
	if (data->line != NULL)
		free_and_null((void *)data->line);
	if (data->path != NULL)
		free_2d_((void **)data->path);
	if (data->real_path != NULL)
		free_2d_((void **)data->real_path);
	if (data->argv != NULL)
		free_2d_((void **)data->argv);
	if (data->env_array != NULL)
		free_2d_((void **)data->env_array);
	if (data->cwd != NULL)
		free_and_null((void *)data->cwd);
	if (data->env != NULL)
		clear_mlist(&data->env);
	if (data->sorted_env != NULL)
		clear_mlist(&data->sorted_env);
	if (data->input != NULL)
		clear_mlist(&data->input);
	if (data->pipelines != NULL)
		clear_mlist(&data->pipelines);
	if (data->pipe_fds != NULL)
		free_2d_((void **)data->pipe_fds);
	if (data->pids != NULL)
		free(data->pids);
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->env = NULL;
	data->sorted_env = NULL;
	// unlink_files(data);
	data->pipelines = NULL;
	data->pipe_fds = NULL;
	data->pids = NULL;
}

void	loop_clean(t_data *data)
{
	free_and_null((void *)data->line);
	if (data->path != NULL)
		free_2d_((void **)data->path);
	if (data->real_path != NULL)
		free_2d_((void **)data->real_path);
	if (data->argv != NULL)
		free_2d_((void **)data->argv);
	if (data->env_array != NULL)
		free_2d_((void **)data->env_array);
	if (data->cwd != NULL)
		free_and_null((void *)data->cwd);
	if (data->input != NULL)
		clear_mlist(&data->input);
	if (data->pipelines != NULL)
		clear_mlist(&data->pipelines);
	if (data->pipe_fds != NULL)
		free_2d_((void **)data->pipe_fds);
	if (data->pids != NULL)
		free(data->pids);
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->pipelines = NULL;
	data->pipe_fds = NULL;
	data->pids = NULL;
}