/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexpander_the_great.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:27:05 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/16 18:06:23 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

static char	*remove_quotes(t_data *data, char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc2(data,ft_strlen(str) - 1, sizeof(char));
	while (str[i] == c)
		str++;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
		while (str[i] == c)
			str++;
	}
	return (res);
}

void	expand_quotes(t_data *data, char **str)
{
	char		*tmp;
	uint32_t	i;

	i = 0;
	tmp = *str;
	while (tmp[i] != '\0')
	{
		if (is_quote(tmp[i]) == true && ft_strchr(&tmp[i + 1], tmp[i]) != NULL)
		{
			*str = remove_quotes(data, tmp, tmp[i]);
			free(tmp);
			return ;
		}
		i++;
	}
}

static void	contract_list(t_data *data, t_mlist *list)
{
	size_t	i;
	char	*tmp;

	while (list != NULL)
	{
		i = ft_strlen(list->str);
		tmp = list->str;
		if (i > 0 && list->str[i - 1] != ' ' && list->nx != NULL)
		{
			list->str = ft_strjoin2(data, tmp, list->nx->str);
			free(tmp);
			unlink_node(list->nx);
		}
		else
		{
			if (list->str[i - 1] == ' ')
				list->str[i - 1] = '\0';
			list = list->nx;
		}
	}
}

void	expansion_pack(t_data *data, char *input)
{
	t_mlist	*split;

	split = ft_special_split(data, input);
	data->input = split;
	if (split == NULL)
		return ;
	while (split != NULL)
	{
		expand_dollar(data, &split->str);
		expand_quotes(data, &split->str);
		split = split->nx;
	}
	contract_list(data, data->input);
	analyze_input(data);
}
