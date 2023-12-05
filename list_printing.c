/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_printing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:05:51 by vincent       #+#    #+#                 */
/*   Updated: 2023/12/05 22:49:03 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_mlist *list)
{
	if (list == NULL)
		return (1);
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
	FILE* file;
	int i = 0;

	file = fopen("tmp.txt", "a");
	if (list == NULL)
	{
		printf("Couldn't print empty list");
		return ;
	}
	list = node_first(list);
	while (list != NULL)
	{
		if (list->str != NULL)
		{
			i++;
			fprintf(file, "%s\n", list->str);
			// printf("token: %d\n\n", list->token);
			fprintf(file, "prev: %p\n", list->pv);
			fprintf(file, "curr: %p\n", list);
			fprintf(file, "next: %p\n", list->nx);
		}
		list = list->nx;
	}
	fprintf(file, "this many lines: %d\n\n", i);
	fclose(file);
}
