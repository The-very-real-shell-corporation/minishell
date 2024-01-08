/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_editing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:03:21 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/08 19:43:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*new_node(t_data *data, char *word, char **args, t_token tolkien)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (new == NULL)
		exit_error(data, "List malloc failed");
	new->str = word; // make sure everything is allocated before it gets in new_node
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
	if (node1 != NULL && node1 != new)
		node1->nx = new;
	if (node2 != NULL && node2 != new)
		node2->pv = new;
}

void	delete_node(t_mlist *node)
{
	if (node->pipeline != NULL)
	{
		free_2d_((void **)node->pipeline);
	}
	if (node->str != NULL)
	{
		free(node->str);
	}
	free(node);
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

t_mlist	*find_input(t_mlist *env, char *input)
{
	while (env != NULL)
	{
		if (ft_ministrcmp(env->str, input) == 0)
			return (env);
		env = env->nx;
	}
	return (NULL);
}

void	unlink_node(t_mlist *node)
{
	t_mlist	*prev;
	t_mlist	*next;

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
	insert_node(node->pv, node, new_node(data, ft_strdup2(data, input), NULL, INITIALIZED));
	unlink_node(node);
}
