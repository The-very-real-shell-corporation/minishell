/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 18:29:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/15 18:58:34 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	clear_mlist(&data->pipelines);
	clear_mlist(&data->input);
	free_2d_((void ***)&data->env_array);
	free_2d_((void ***)&data->path);
	free_2d_((void ***)&data->real_path);
	data->pipe_fds[0][READ] = -1;
	data->pipe_fds[0][WRITE] = -1;
	data->pipe_fds[1][READ] = -1;
	data->pipe_fds[1][WRITE] = -1;
}

void	clean_up(t_data *data)
{
	loop_clean(data);
	clear_mlist(&data->env);
	rl_clear_history();
}
