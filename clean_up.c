/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_up.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 18:29:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/09 09:46:57 by lotse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2D(char **input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return ;
	while (input[i] != NULL)
	{
		free(input[i]);
		i++;
	}
	free(input);
	input = NULL;
}

void	clean_up(t_data *data)
{
	if (data->path != NULL)
		free_2D(data->path);
	if (data->real_path != NULL)
		free_2D(data->real_path);
	if (data->argv != NULL)
		free_2D(data->argv);
	if (data->env_array != NULL)
		free_2D(data->env_array);
	if (data->cwd != NULL)
		free(data->cwd);
	if (data->env != NULL)
		clear_mlist(&data->env);
	if (data->sorted_env != NULL)
		clear_mlist(&data->sorted_env);
	if (data->input != NULL)
		clear_mlist(&data->input);
}
