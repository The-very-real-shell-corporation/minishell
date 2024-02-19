/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_printing.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:05:51 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/19 18:08:41 by vvan-der      ########   odam.nl         */
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
			ft_putendl_fd(list->str, STDOUT_FILENO);
		list = list->nx;
	}
	return (0);
}

void	print_list(t_mlist *list)
{
	if (list == NULL)
	{
		ft_putendl_fd("Couldn't print empty list", STDERR_FILENO);
		return ;
	}
	while (list != NULL)
	{
		ft_putendl_fd(list->str, STDOUT_FILENO);
		list = list->nx;
	}
}
