/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 18:29:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/04 21:08:05 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_(char **input)
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
		free_2d_(data->path);
	if (data->real_path != NULL)
		free_2d_(data->real_path);
	if (data->argv != NULL)
		free_2d_(data->argv);
	if (data->env_array != NULL)
		free_2d_(data->env_array);
	// if (data->cwd != NULL)
	// 	free_and_null((void *)data->cwd);
	if (data->cwd != NULL)
	{
		free(data->cwd);
		data->cwd = NULL;
	}
	if (data->env != NULL)
		clear_mlist(&data->env);
	if (data->sorted_env != NULL)
		clear_mlist(&data->sorted_env);
	if (data->input != NULL)
		clear_mlist(&data->input);
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->env = NULL;
	data->sorted_env = NULL;	
}

void	loop_clean(t_data *data)
{
	free_and_null((void *)data->line);
	printf("data->path: %p\n", data->path);
	if (data->path != NULL)
		free_2d_(data->path);
	if (data->real_path != NULL)
		free_2d_(data->real_path);
	if (data->argv != NULL)
		free_2d_(data->argv);
	if (data->env_array != NULL)
		free_2d_(data->env_array);
	// if (data->cwd != NULL)
	// 	free_and_null((void *)data->cwd);
	if (data->cwd != NULL)
	{
		free(data->cwd);
		data->cwd = NULL;
	}
	if (data->input != NULL)
		clear_mlist(&data->input);
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	printf("data->path: %p\n", data->path);
}