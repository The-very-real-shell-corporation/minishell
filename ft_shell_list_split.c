/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shell_list_split.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:00:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/03 13:51:36 by vvan-der      ########   odam.nl         */
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
	if (triple == true)
		ft_strcpy(&dest[i + 1], &src[2]);
	else
		ft_strcpy(&dest[i + 1], &src[1]);
}

static char	*read_string(char *input)
{
	char	*new_input;
	char	c;
	int		i;
	int		x;

	i = 0;
	x = 0;
	new_input = ft_strdup(input);
	while (input[i])
	{
		if (ft_strchr("\"\'", input[i]) != NULL)
		{
			c = input[i];
			i++;
			if (input[i] == c)
			{
				x += 2;
				new_input = ft_realloc(new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i - 1], i + x, true);
			}
			while (input[i] != c && input[i] != '\0')
				i++;
		}
		else if (ft_strchr("|;$><", input[i]) != NULL)
		{
			x += 2;
			if (ft_strchr("><", input[i+1]) != NULL && input[i] == input[i+1])
			{
				new_input = ft_realloc(new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i], i + x + 1, true);
				// printf("Edited input (double edit): %s\n", new_input);
				i++;
			}
			else
			{
				new_input = ft_realloc(new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i], i + x, false);
				// printf("Edited input (single edit): %s\n", new_input);
			}
		}
		if (input[i] != '\0')
			i++;
	}
	return (new_input);
}

static char	*fix_input(char *input)
{
	char	*new_input;

	new_input = read_string(input);
	return (new_input);
}

t_mlist	*ft_shell_list_split(char *input)
{
	int 	i;
	int		start;
	int		end;
	t_mlist	*list;

	i = 0;
	list = NULL;
	input = fix_input(input);
	if (input == NULL)
		return (NULL);
	printf("input: %s\n", input);
	while (input[i] != '\0')
	{
		while (ft_iswhitespace(input[i]) == true)
			i++;
		start = i;
		if (ft_strchr("\'\"", input[i]) != NULL)
		{
			i++;
			while (input[i] != '\0' && input[i] != input[start])
				i++;
			if (input[i] == input[start])
				i++;
		}
		else
		{
			while (input[i] != '\0' && ft_iswhitespace(input[i]) == false)
				i++;
		}
		end = i;
		if (start != end)
			node_addback(&list, (new_node(make_word(input, start, end))));
	}
	free(input);
	return (list);
}
