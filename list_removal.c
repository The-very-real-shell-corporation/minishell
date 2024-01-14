/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_removal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 15:14:42 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/14 17:14:47 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_mlist *node)
{
	if (node->pipeline != NULL)
	{
		free_2d_((void ***)&node->pipeline);
	}
	if (node->str != NULL)
	{
		free(node->str);
	}
	free_and_null((void **)&node);
}

void	clear_mlist(t_mlist **list)
{
	t_mlist	*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->nx;
		delete_node(tmp);
	}
}

void	unlink_node(t_mlist *node)
{
	t_mlist	*prev;
	t_mlist	*next;

	if (node == NULL)
		return ;
	prev = node->pv;
	next = node->nx;
	if (prev != NULL)
		prev->nx = next;
	if (next != NULL)
		next->pv = prev;
	delete_node(node);
}

void	replace_node(t_data *data, t_mlist *node, char *input)
{
	insert_node(node->pv, node, \
	new_node(data, ft_strdup2(data, input), NULL, INITIALIZED));
	unlink_node(node);
}
