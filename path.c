/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 15:15:18 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/10 18:35:13 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path_ready(t_data *data)
{
	data->path = ft_split(getenv("PATH"), ':');
	if (data->path == NULL)
		exit_error(data, "Split error\n");
}

	// DIR		*directory;
	// struct dirent	*result;
	// int i = 0;
	
/*	print_2Dcharray(data->path);
	directory = opendir(path[i]);
	while (path[i] != NULL)
	{
		if (directory != NULL)
			result = readdir(directory);
		if (result != NULL)
			printf("%s\n", result->d_name);
		if (result == NULL)
		{
			if (directory != NULL)
				closedir(directory);
			i++;
			directory = opendir(path[i]);
			while (directory == NULL && path[i] != NULL)
			{
				directory = opendir(path[i]);
				i++;
			}
		}
	} */