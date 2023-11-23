/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexpander.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:27:05 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/21 18:34:46 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

static char	*remove_quotes(char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (res == NULL)
		return (NULL);
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
		if (is_quote(tmp[i]) == true)
		{
			*str = remove_quotes(tmp, tmp[i]);
			if (*str == NULL)
				exit_error(data, "malloc fail");
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
		if (list->str[i - 1] != ' ' && list->nx != NULL)
		{
			list->str = ft_strjoin(tmp, list->nx->str);
			if (list->str == NULL)
				exit_error(data, "malloc error");
			free(tmp);
			unlink_node(list->nx);
		}
		else
			list = list->nx;
	}
}

void	expansion_pack(t_data *data, char *input)
{
	t_mlist	*split;

	split = ft_special_split(data, input);
	data->input = split;
	if (split == NULL)
		return ;
	puts("Before expo");
	print_list(data->input);
	while (split != NULL)
	{
		expand_dollar(data, &split->str);
		expand_quotes(data, &split->str);
		split = split->nx;
	}
	// puts("After expo");
	// print_list(data->input);
	contract_list(data, data->input);
	puts("After contraction");
	print_list(data->input);
	analyze_input(data);
}
