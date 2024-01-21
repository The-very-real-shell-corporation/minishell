/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_navigate2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 19:50:48 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 17:38:53 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	re_tokens(t_mlist *list)
{
	size_t	count;

	count = 0;
	while (list != NULL)
	{
		if (is_redirection(list->token) == true)
			count++;
		list = list->nx;
	}
	return (count);
}