/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_navigate2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 19:50:48 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/16 19:52:05 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_tokens(t_mlist *list, t_token tolkien)
{
	size_t	count;

	count = 0;
	while (list != NULL)
	{
		if (list->token == tolkien)
			count++;
		list = list->nx;
	}
	return (count);
}