/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_special_split.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 14:31:00 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/15 18:00:11 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	token_chars(char c)
{
	char	values[] = {'|', '>', '<', 9, 10, 11, 12, 13, 32, '\0'};
	int		i;

	i = 0;
	while (values[i] != '\0')
	{
		if (values[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static int	get_token_length(char *str)
{
	if (str[0] == '|')
		return (1);
	if (str[1] == str[0])
		return (2);
	else
		return (1);
}

static size_t	get_length(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && token_chars(str[i]) == false)
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"') != NULL)
		{
			i += ft_strchr(&str[i + 1], '\"') - &str[i];
			return (i + 1);
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'') != NULL)
		{
			i += ft_strchr(&str[i + 1], '\'') - &str[i];
			return (i + 1);
		}
		i++;
	}
	return (i);
}

t_mlist	*ft_special_split(t_data *data, char *input)
{
	t_mlist	*res;
	int		i;
	int		len;

	i = 0;
	len = 0;
	res = NULL;
	while (input[i] != '\0')
	{
		while (input[i] != '\0' && ft_iswhitespace(input[i]) == true)
			i++;
		if (token_chars(input[i]) == true)
			len = get_token_length(&input[i]);
		else
			len = get_length(&input[i]);
		if (ft_iswhitespace(input[i + len]) == true)
			len++;
		node_addback(&res, new_node(data, mini_substring(data, &input[i], len)));
		if (len != 0)
			i += len;
		else
			i++;
	}
	return (res);
}