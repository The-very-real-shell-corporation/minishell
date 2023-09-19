/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:03:21 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 18:17:27 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_mlist *list)
{
	int	i;

	i = 0;
	if (!list)
		return ;
	while (list != NULL)
	{
		if (list->str != NULL)
			printf("node [%d]:	%s\n", i, list->str);
		printf("Address:	%p\n", list);
		list = list->nx;
		i++;
	}
}

t_mlist	*node_last(t_mlist *list)
{
	while (list->nx != NULL)
	{
		list = list->nx;
	}
	return (list);
}

t_mlist	*new_node(char *word)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (!new)
		exit_error("List malloc failed");
	new->str = word;
	new->token = INITIALIZED;
	new->nx = NULL;
	new->pv = NULL;
	return (new);
}

void	node_addback(t_mlist **list, t_mlist *new_node)
{
	t_mlist	*tmp;

	if (!*list)
		*list = new_node;
	else
	{
		tmp = *list;
		*list = node_last(*list);
		(*list)->nx = new_node;
		new_node->pv = *list;
		*list = tmp;
	}
}

void	clear_mlist(t_mlist **list)
{
	t_mlist	*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->nx;
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
	}
	list = NULL;
}
