/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 18:29:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/16 20:07:22 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipelines(t_data *data, t_mlist **pipelines)
{
	while (*pipelines != NULL)
	{
		clear_mlist(pipelines);
		pipelines++;
	}
	free_and_null((void **)&data->pipelines);
}

void	free_and_null(void **variable)
{
	free(*variable);
	*variable = NULL;
}

void	free_2d_(void ***input)
{
	int		i;
	void	**array;

	if (*input == NULL)
		return ;
	array = *input;
	i = 0;
	while (array[i] != NULL)
	{
		free_and_null(&array[i]);
		i++;
	}
	free(array);
	*input = NULL;
}

void	loop_clean(t_data *data)
{
	free_pipelines(data, data->pipelines);
	clear_mlist(&data->input);
	free_2d_((void ***)&data->argv);
	free_2d_((void ***)&data->env_array);
	free_2d_((void ***)&data->delim);
	free_2d_((void ***)&data->path);
	free_2d_((void ***)&data->real_path);
	free_and_null((void **)&data->cwd);
	free_and_null((void **)&data->line);
	free_and_null((void **)&data->pids);
}

void	clean_up(t_data *data)
{
	loop_clean(data);
	clear_mlist(&data->env);
}
