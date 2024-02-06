/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexpander_the_great.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:27:05 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/06 17:12:11 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char c)
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
	res = ft_calloc2(data, ft_strlen(str) - 1, sizeof(char));
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

void	expand_quotes(t_data *data, t_mlist *node, char **str)
{
	char		*tmp;
	uint32_t	i;

	i = 0;
	tmp = *str;
	while (tmp[i] != '\0')
	{
		if (is_quote(tmp[i]) == true && ft_strchr(&tmp[i + 1], tmp[i]) != NULL)
		{
			if (tmp[ft_strlen(tmp) - 1] != ' ')
				node->token = STITCH;
			*str = remove_quotes(data, tmp, tmp[i]);
			free(tmp);
			return ;
		}
		i++;
	}
}

static void	contract_list(t_data *data, t_mlist *list)
{
	char	*tmp;
	int		pos;

	while (list->nx != NULL)
	{
		tmp = list->str;
		if (list->token == STITCH)
		{
			list->str = ft_strjoin2(data, tmp, list->nx->str);
			free(tmp);
			unlink_node(list->nx);
		}
		else if (tmp[ft_strlen(tmp) - 1] == ' ')
		{
			list->str[ft_strlen(tmp) - 1] = '\0';
			list = list->nx;
		}
		else
			list = list->nx;
	}
	pos = ft_strlen(list->str);
	if (pos > 0 && list->str[pos - 1] == ' ')
		list->str[pos - 1] = '\0';
}

void	expansion_pack(t_data *data, char *input_str)
{
	t_mlist	*split;

	split = ft_special_split(data, input_str);
	data->input = split;
	if (split == NULL)
		return ;
	while (split != NULL)
	{
		expand_dollar(data, &split->str);
		journey_to_alexpandria(data, &split, split->str);
		expand_quotes(data, split, &split->str);
		split = split->nx;
	}
	contract_list(data, data->input);
	tokenize_list(data, data->input);
}
