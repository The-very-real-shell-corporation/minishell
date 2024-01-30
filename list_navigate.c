/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_navigate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:04:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/30 15:14:06 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

size_t	list_size(t_mlist *list, t_token tolkien)
{
	size_t	i;

	i = 0;
	while (list != NULL && list->token != tolkien)
	{
		list = list->nx;
		i++;
	}
	return (i);
}

bool	go_to_token(t_mlist **list, t_token tolkien)
{
	t_mlist	*tmp;

	tmp = *list;
	while (*list != NULL && (*list)->token != tolkien)
		*list = (*list)->nx;
	if (*list == NULL)
	{
		*list = tmp;
		return (false);
	}
	return (true);
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
