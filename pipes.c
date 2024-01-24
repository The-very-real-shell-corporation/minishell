/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 14:56:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/24 12:28:54 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_pipelines(t_data *data, t_mlist *in, t_mlist **pipelines)
{
	char 	**arr;

	while (in != NULL)
	{
		arr = list_to_array(data, in);
		if (arr != NULL)
			node_addback(pipelines, new_node(data, NULL, arr, in->token));
		while (in != NULL && is_redirection(in->token) == NONE)
			in = in->nx;
		if (in != NULL && is_redirection(in->token) != NONE)
		{
			node_addback(pipelines, \
			new_node(data, ft_strdup2(data, in->str), NULL, in->token));
			in = in->nx;
		}
	}
	puts("\nPipelines: \n");
	print_list(data->pipelines);
	// exit(0);
}
