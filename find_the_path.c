/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_the_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 17:13:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/09 18:57:39 by vvan-der      ########   odam.nl         */
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
			directory = ft_strjoin2(data, data->real_path[i], data->argv[0]);
			chdir(data->cwd);
			execute_command(data, directory, data->argv);
		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup2(data, data->argv[0]), data->argv);
	exit(EXIT_FAILURE);
}

void	get_path_ready(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = envp_string(data, ft_strdup2(data, "PATH"));
	data->path = ft_split(tmp, ':');
	if (data->path == NULL)
	{
		free(tmp);
		exit_error(data, "Split error");
	}
	free(tmp);
	data->real_path = ft_calloc(ptr_array_size((void **)data->path) \
						+ 1, sizeof(char *));
	while (data->path[i] != NULL)
	{
		data->real_path[i] = ft_strjoin2(data, data->path[i], "/");
		i++;
	}
}
