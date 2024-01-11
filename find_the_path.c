/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_the_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 17:13:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 18:37:03 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_the_path(t_data *data, t_mlist *p, char **path)
{
	int		i;
	char	*directory;

	i = 0;
	data->env_array = list_to_array(data, data->env, DUMMY);
	while (path[i] != NULL)
	{
		chdir(path[i]);
		if (access(data->argv[0], X_OK) == 0)
		{
			directory = ft_strjoin2(data, data->real_path[i], p->pipeline[0]);
			chdir(data->cwd);
			execute_command(data, directory, p->pipeline);
		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->argv[0], X_OK) == 0)
		execute_command(data, ft_strdup2(data, p->pipeline[0]), p->pipeline);
	exit(54); // look up a smart exit status
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
	data->real_path = ft_calloc2(data, ptr_array_size((void **)data->path) \
						+ 1, sizeof(char *));
	while (data->path[i] != NULL)
	{
		data->real_path[i] = ft_strjoin2(data, data->path[i], "/");
		i++;
	}
}
