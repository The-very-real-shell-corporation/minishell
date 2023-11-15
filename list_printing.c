/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_printing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:05:51 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/15 18:00:43 by vincent       ########   odam.nl         */
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
	}
}