/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_printing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:05:51 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/30 15:22:38 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_mlist *list)
{
	if (list == NULL)
		return (-1);
	list = node_first(list);
	while (list != NULL)
	{
		if (ft_strchr(list->str, '=') != NULL)
			printf("%s\n", list->str);
		list = list->nx;
	}
	return (0);
}

void	print_list(t_mlist *list)
{
	if (list == NULL)
	{
		printf("Couldn't print empty list\n");
		return ;
	}
	while (list != NULL)
	{
		printf("%s\n", list->str);
		list = list->nx;
	}
}

/* void	print_list(t_mlist *list)
{
	if (list == NULL)
	{
		printf("Couldn't print empty list\n");
		return ;
	}
	while (list != NULL)
	{
		printf("string: %s\n", list->str);
		print_2d_charray(list->args);
		printf("token: %d\n", list->token);
		list = list->nx;
		printf("\nNEXT\n\n");
	}
	printf("%p\n", list);
} */
