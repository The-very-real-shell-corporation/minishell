/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_navigate2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 19:50:48 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/24 11:49:32 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	re_tokens(t_mlist *list)
{
	size_t	count;

	count = 0;
	while (list != NULL)
	{
		if (is_redirection(list->token) != NONE)
			count++;
		list = list->nx;
	}
	return (count);
}

size_t	list_size_redirection(t_mlist *list)
{
	size_t	i;

	i = 0;
	while (list != NULL)
	{
		if (is_redirection(list->token) != NONE)
		{
			if (list->token == HEREDOC)
				i++;
			break ;
		}
		list = list->nx;
		i++;
	}
	return (i);
}
