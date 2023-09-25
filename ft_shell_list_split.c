/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shell_list_split.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:00:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 15:33:52 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_string(char *dest, char *src, int i, bool triple)
{
	if (triple == true)
	{
		dest[i - 3] = ' ';
		dest[i - 2] = *src;
	}
	else
		dest[i - 2] = ' ';
	dest[i - 1] = *src;
	dest[i] = ' ';
}

static char	*read_string(char *input)
{
	char	*new_input;
	int		i;
	int		x;

	i = 0;
	x = 0;
	new_input = ft_strdup(input);
	while (input[i])
	{
		if (ft_strchr("|;$><", input[i]) != NULL)
		{
			x += 2;
			if (ft_strchr("><", input[i+1]) != NULL && input[i] == input[i+1])
			{
				x++;
				new_input = ft_realloc(new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i], i + x, true);
			}
			else
			{
				new_input = ft_realloc(new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i], i + x, false);
			}
		}
		i++;
	}
	return (new_input);
}

static char	*fix_input(char *input)
{
	char	*new_input;

	if (ft_strchr("|><;", *input) != NULL)
		return (free(input), NULL);
	new_input = read_string(input);
	return (new_input);
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
	if (input == NULL)
		return (NULL);
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
