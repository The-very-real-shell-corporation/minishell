/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shell_list_split.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:00:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 16:02:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fix_input(char *input)
{
	char	*new_input;
	int		i;

	i = 0;
	if (ft_strchr("|><;", input[i]) != NULL)
		return (free(input), NULL);
	new_input = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!new_input)
		exit_error("Malloc error");
	while (input[i])
	{
		new_input[i] = input[i];
		if (ft_strchr("|><;", input[i]) != NULL)
			
		i++;
	}
}

static char	*make_word(char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((end - start + 1), sizeof(char));
	if (!word)
		exit_error("Malloc error");
	while (start < end)
	{
			
		word[i] = str[start];
		i++;
		start++;
	}
	return (word);
}

t_mlist	*ft_shell_list_split(char *input)
{
	int i;
	int	start;
	int	end;
	t_mlist	*list;

	list = NULL;
	input = fix_input(input);
	while (input[i])
	{
		while (ft_iswhitespace(input[i]) == true)
			i++;
		start = i;
		while (ft_iswhitespace(input[i]) == false)
			i++;
		end = i;
		node_addback(&list, (new_node(make_word(input, start, end))));
	}
	return (list);
}
