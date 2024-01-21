/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_the_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 17:13:46 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 18:06:53 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_the_path(t_data *data, t_mlist *p, char **path)
{
	int		i;
	char	*directory;

	i = 0;
	data->env_array = list_to_array(data, data->env);
	while (path[i] != NULL)
	{
		chdir(path[i]);
		if (access(data->args[0], X_OK) == 0)
		{
			directory = ft_strjoin2(data, data->real_path[i], p->pipeline[0]);
			chdir(data->cwd);
			execute_command(data, directory, p->pipeline);
		}
		i++;
	}
	chdir(data->cwd);
	if (access(data->args[0], X_OK) == 0)
		execute_command(data, ft_strdup2(data, p->pipeline[0]), p->pipeline);
	exit(54); // look up a smart exit status
}

