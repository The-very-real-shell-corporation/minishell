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

	new = ft_calloc2(data, 1, sizeof(t_mlist));
	new->str = word;
	new->args = args;
	new->token = tolkien;
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

t_mlist	*copy_node(t_data *data, t_mlist *node)
{
	t_mlist	*copy;
	size_t	i;

	i = 0;
	copy = new_node(data, NULL, NULL, INIT);
	copy->str = ft_strdup2(data, node->str);
	copy->token = node->token;
	if (node->args != NULL)
		copy->args = ft_calloc2(data, \
		ptr_array_size((void **)node->args) + 1, sizeof(char *));
	else
		return (copy);
	while (node->args[i] != NULL)
	{
		copy->args[i] = ft_strdup2(data, node->args[i]);
		i++;
	}
	return (copy);
}
