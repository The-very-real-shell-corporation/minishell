/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:00:43 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/15 20:16:33 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_quotes(bool *single_q, bool *double_q, char *str)
{
	if (str[0] == '\'' && *double_q == false)
	{
		if (*single_q == true)
			*single_q = false;
		else if (*single_q == false && ft_strchr(&str[1], '\'') != NULL)
			*single_q = true;
	}
	else if (str[0] == '\"' && *single_q == false)
	{
		if (*double_q == true)
			*double_q = false;
		else if (*double_q == false && ft_strchr(&str[1], '\"') != NULL)
			*double_q = true;
	}
}

static uint32_t	get_length(char *str)
{
	uint32_t	i;

	i = 0;
	while (str[i] != '\0' && ft_iswhitespace(str[i]) == false \
	&& ft_strchr("\'\"$", str[i]) == NULL)
	{
		i++;
	}
	return (i);
}

static char	*rewrite_string(t_data *data, char *original, int start)
{
	uint32_t	len;
	char		*variable;
	char		*value;
	char		*new_string;

	len = get_length(&original[start + 1]);
	variable = ft_calloc(len + 1, sizeof(char));
	if (variable == NULL)
		exit_error(data, "malloc fail");
	ft_strlcpy(variable, &original[start + 1], len + 1);
	value = env_string(data, variable);
	new_string = partially_merge_str(original, start, len + 1, value);
	if (new_string == NULL)
		exit_error(data, "malloc fail");
	return (new_string);
}

void	expand_dollar(t_data *data, char **str)
{
	bool		single_q;
	bool		double_q;
	char		*tmp;
	uint32_t	i;

	single_q = false;
	double_q = false;
	i = 0;
	tmp = *str;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '$' && single_q == false && tmp[i + 1] != '\0')
		{
			*str = rewrite_string(data, tmp, i);
			expand_dollar(data, str);
			return ;
		}
		edit_quotes(&single_q, &double_q, &tmp[i]);
		i++;
	}
}
