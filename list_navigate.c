/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_navigate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:04:09 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/15 16:05:39 by vincent       ########   odam.nl         */
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
