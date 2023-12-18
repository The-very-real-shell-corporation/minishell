/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_the_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 17:13:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/18 19:58:31 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_the_path(t_data *data, char **path)
{
	int		i;
	char	*directory;

	i = 0;
	data->env_array = list_to_array(data, data->env);
	while (path[i] != NULL)
	{
		chdir(path[i]);
		if (access(data->argv[0], X_OK) == 0)
		{
			directory = ft_strjoin(data->real_path[i], data->argv[0]);
			chdir(data->cwd);
			execute_command(data, directory);
		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup(data->argv[0]));
	exit(EXIT_FAILURE); // look up a smart exit status
}

void	get_path_ready(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = env_string(data, "PATH");
	data->path = ft_split(tmp, ':');
	if (data->path == NULL)
	{
		free(tmp);
		exit_error(data, "Split error\n");
	}
	free(tmp);
	while (data->path[i] != NULL)
		i++;
	data->real_path = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	while (data->path[i] != NULL)
	{
		data->real_path[i] = ft_strjoin(data->path[i], "/");
		if (data->real_path[i] == NULL)
			exit_error(data, "strjoin failed");
		i++;
	}
}
