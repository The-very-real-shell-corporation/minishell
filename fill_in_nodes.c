/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_in_nodes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:19:57 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/02 15:42:02 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_word(char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((end - start + 1), sizeof(char));
	if (word == NULL)
		exit_error("Malloc error");
	while (start + i < end)
	{
		word[i] = str[start + i];
		i++;
	}
	return (word);
}
