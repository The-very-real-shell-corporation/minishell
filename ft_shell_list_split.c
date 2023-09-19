/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shell_list_split.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:00:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 18:39:24 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fix_input(char *input)
{
	char	*new_input;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (ft_strchr("|><;", input[i]) != NULL)
		return (free(input), NULL);
	new_input = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!new_input)
		exit_error("Malloc error");
	while (input[i])
	{
		if (ft_strchr("|><;", input[i]) != NULL)
		{
			x += 2;
			new_input = ft_realloc(new_input, ft_strlen(input) + x + 1);
			new_input[i + x - 2] = ' ';
			new_input[i + x - 1] = input[i];
			new_input[i + x] = ' ';
		}
		else
			new_input[i + x] = input[i];
		i++;
	}
	return (free(input), new_input);
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

	i = 0;
	list = NULL;
	input = fix_input(input);
	// if (!input)
	// 	return (NULL);
	while (input[i])
	{
		while (ft_iswhitespace(input[i]) == true)
			i++;
		start = i;
		while (input[i] && ft_iswhitespace(input[i]) == false)
			i++;
		end = i;
		if (start != end)
			node_addback(&list, (new_node(make_word(input, start, end))));
	}
	// print_list(list);
	return (list);
}
