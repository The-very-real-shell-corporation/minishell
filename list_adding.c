/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_adding.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:03:21 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 15:15:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*new_node(t_data *data, char *word, char **args, t_token tolkien)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (new == NULL)
		exit_error(data, "List malloc failed");
	new->str = word;
	new->pipeline = args;
	new->token = tolkien;
	new->nx = NULL;
	new->pv = NULL;
	return (new);
}

void	node_addback(t_mlist **list, t_mlist *new_node)
{
	if (*list == NULL)
		*list = new_node;
	else
	{
		*list = node_last(*list);
		(*list)->nx = new_node;
		new_node->pv = *list;
		*list = node_first(*list);
	}
}

void	insert_node(t_mlist *node1, t_mlist *node2, t_mlist *new)
{
	new->pv = node1;
	new->nx = node2;
	if (node1 != NULL)
		node1->nx = new;
	if (node2 != NULL)
		node2->pv = new;
}

void	insert_list(t_mlist *node1, t_mlist *node2, t_mlist *list)
{
	t_mlist	*tmp;

	list->pv = node1;
	if (node1 != NULL)
		node1->nx = list;
	tmp = node_last(list);
	tmp->nx = node2;
	if (node2 != NULL)
		node2->pv = tmp;
}
