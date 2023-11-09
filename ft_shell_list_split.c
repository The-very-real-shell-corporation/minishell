/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shell_list_split.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 13:00:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/09 09:40:35 by lotse         ########   odam.nl         */
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
	ft_strcpy(&dest[i + 1], &src[1]);
}

static char	*read_string(t_data *data, char *input)
{
	char	*new_input;
	char	c;
	int		i;
	int		x;

	i = 0;
	x = 0;
	new_input = ft_strdup2(data, input);
	while (input[i])
	{
		if (ft_strchr("\"\'", input[i]) != NULL)
		{
			c = input[i];
			i++;
			if (input[i] == c)
			{
				x += 2;
				new_input = ft_realloc(data, new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i], i + x, true);
			}
			while (input[i] != c && input[i] != '\0')
				i++;
		}
		else if (ft_strchr("|$><", input[i]) != NULL)
		{
			x += 2;
			if (ft_strchr("><", input[i + 1]) != NULL && input[i] == input[i + 1])
			{
				new_input = ft_realloc(data, new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i + 1], i + x + 1, true);
				i++;
			}
			else
			{
				new_input = ft_realloc(data, new_input, ft_strlen(input) + x + 1);
				edit_string(new_input, &input[i], i + x, false);
			}
		}
		if (input[i] != '\0')
			i++;
	}
	return (new_input);
}

// static char	*fix_input(t_data *data, char *input)
// {
// 	char	*new_input;

// 	new_input = read_string(data, input);
// 	return (new_input);
// }

t_mlist	*ft_shell_list_split(t_data *data, char *input)
{
	int 	i;
	int		start;
	int		end;
	char	*tmp;
	t_mlist	*list;
	t_mlist	*node;

	i = 0;
	list = NULL;
	input = read_string(data, input);
	if (input == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		while (input[i] != '\0' && ft_iswhitespace(input[i]) == true)
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
			while (ft_strchr("\'\"", input[i]) == NULL \
			&& ft_iswhitespace(input[i]) == false && input[i] != '\0')
				i++;
		}
		end = i;
		if (start != end)
		{
			tmp = make_word(data, input, start, end);
			node = new_node(data, tmp);
			free(tmp);
			node_addback(&list, node);
		}
	}
	print_list(list);
	free(input);
	return (list);
}
