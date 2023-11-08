/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_the_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 17:13:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/08 14:09:28 by lotse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**list_to_array(t_data *data ,t_mlist *list)
{
	char 	**result;
	size_t	i;

	result = ft_calloc((list_size(list) + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		result[i] = ft_strdup2(data, list->str);
		// if (result[i] == NULL)
		// 	return (free_2Darray(result), NULL);
		list = list->nx;
		i++;
	}
	return (result);
}

bool	search_the_path(t_data *data, char **path)
{
	int		i;
	char	*directory;

	i = 0;
	data->cwd = getcwd(NULL, 0);
	data->env_array = list_to_array(data, data->env);
	data->argv = list_to_array(data, data->input);
	while (path[i] != NULL)
	{
		chdir(path[i]);
		if (access(data->argv[0], X_OK) == 0)
		{
			directory = ft_strjoin(data->real_path[i], data->argv[0]);
			chdir(data->cwd);
			if (execve(directory, data->argv, data->env_array) == -1)
				printf("Error: could not execute\n");
			free(directory);
			return (true);
		}
		i++;
	}
	chdir(data->cwd);
	return (false);
}

void	get_path_ready(t_data *data)
{
	int		i;

	i = 0;
	data->path = ft_split(getenv("PATH"), ':'); // change "PATH" to the Path variable in our environment
	if (data->path == NULL)
		exit_error(data, "Split error\n");
	while (data->path[i] != NULL)
		i++;
	data->real_path = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (data->path[i] != NULL)
	{
		data->real_path[i] = ft_strjoin(data->path[i], "/");
		// if (data->real_path[i] == NULL)
		// 	free_2D_array(data->real_path);
		i++;
	}
}
