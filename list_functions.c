/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:03:21 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 19:05:32 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			printf("node [%d]:	%s\n", i, list->str);
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
	if (!new)
		exit_error(data, "List malloc failed");
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

void	insert_node(t_mlist **node1, t_mlist **node2, t_mlist *new)
{
	new->pv = *node1;
	new->nx = *node2;
	if (*node1 != NULL && *node1 != new)
		(*node1)->nx = new;
	if (*node2 != NULL && *node2 != new)
		(*node2)->pv = new;
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

bool	find_input(t_data *data, char *input)
{
	t_mlist	*tmp;

	tmp = data->env;
	while (data->env != NULL)
	{
		if (ft_ministrncmp(data->env->str, input) != 0)
			data->env = data->env->nx;
		else
		{
			data->env->str = ft_realloc(data, input, ft_strlen(input) + 1);
			data->env = tmp;
			return (true);
		}
	}
	data->env = tmp;
	return (false);
}
