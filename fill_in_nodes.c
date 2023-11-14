/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_in_nodes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:19:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/14 17:43:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mini_substring(t_data *data, char *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((len + 1), sizeof(char));
	if (word == NULL)
		exit_error(data, "Malloc error");
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}
