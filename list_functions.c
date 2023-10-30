/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:03:21 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/30 17:50:23 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	list_size(t_mlist *list)
{
	size_t	i;

	i = 0;
	while (list != NULL)
	{
		list = list->nx;
		i++;
	}
	return (i);
}

void	print_env(t_mlist *list)
{
	if (list == NULL)
	{
		puts("HALP CANT PRINT OMFG");
		return ;
	}
	list = node_first(list);
	while (list != NULL)
	{
		if (ft_strchr(list->str, '=') != NULL)
			printf("%s\n", list->str);
		list = list->nx;
	}
}

void	print_list(t_mlist *list)
{
	int	i;

	i = 0;
	if (list == NULL)
	{
		puts("HALP CANT PRINT OMFG");
		return ;
	}
	list = node_first(list);
	while (list != NULL)
	{
		if (list->str != NULL)
		{
			printf("%s\n", list->str);
			// printf("node [%d]:	%s\n", i, list->str);
			// printf("token: %d\n\n", list->token);
			// printf("Prev:		%p\n", list->pv);
			// printf("Address:	%p\n", list);
			// printf("Next:		%p\n", list->nx);
		}
		list = list->nx;
		i++;
	}
}

t_mlist	*node_first(t_mlist *list)
{
	while (list->pv != NULL)
		list = list->pv;
	return (list);
}

t_mlist	*node_last(t_mlist *list)
{
	while (list->nx != NULL)
		list = list->nx;
	return (list);
}

t_mlist	*new_node(t_data *data, char *word)
{
	t_mlist	*new;

	new = malloc(sizeof(t_mlist));
	if (new == NULL)
		exit_error(data, "List malloc failed");
	new->str = ft_strdup(word);
	if (new->str == NULL)
	{
		free(new);
		exit_error(data, "Malloc fail");
	}
	new->token = INITIALIZED;
	new->nx = NULL;
	new->pv = NULL;
	return (new);
}

void	node_addback(t_mlist **list, t_mlist *new_node)
{
	if (!*list)
		*list = new_node;
	else
	{
		*list = node_last(*list);
		(*list)->nx = new_node;
		new_node->pv = *list;
		*list = node_first(*list);
	}
}

void	insert_node(t_mlist **node1, t_mlist **node2, t_mlist *new)
{
	new->pv = *node1;
	new->nx = *node2;
	if (*node1 != NULL && *node1 != new)
		(*node1)->nx = new;
	if (*node2 != NULL && *node2 != new)
		(*node2)->pv = new;
}

void	delete_node(t_mlist *node)
{
	if (node->str != NULL)
	{
		printf("Str about to be deleted: %s\n", node->str);
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
	list = NULL;
}

t_mlist	*find_input(t_mlist *env, char *input)
{
	while (env != NULL)
	{
		if (ft_ministrncmp(env->str, input) == 0)
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
	insert_node(&node->pv, &node, new_node(data, input));
	unlink_node(node);
}