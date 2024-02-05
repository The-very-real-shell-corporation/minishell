/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:00:43 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/05 16:23:16 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_quotes(bool *single_q, bool *double_q, char *str)
{
	if (*str == '\'' && *double_q == false)
	{
		if (*single_q == true)
			*single_q = false;
		else if (*single_q == false && ft_strchr(&str[1], '\'') != NULL)
			*single_q = true;
	}
	else if (*str == '\"' && *single_q == false)
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
	&& ft_strchr("\'\"$=", str[i]) == NULL)
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
	variable = ft_calloc2(data, len + 1, sizeof(char));
	ft_strlcpy(variable, &original[start + 1], len + 1);
	value = envp_string(data, variable);
	free(variable);
	new_string = remake_str(original, start, len + 1, value);
	if (new_string == NULL)
		exit_error(data, "malloc fail");
	return (new_string);
}

static bool	expand_more(t_data *data, char *tmp, char **str, int i)
{
	if (tmp[i + 1] == '?')
	{
		if (i == 0 || tmp[i - 1] != '\\')
		{
			*str = remake_str(tmp, i, 2, ft_itoa2(data, data->exit_status));
			if (*str == NULL)
				exit_error(data, "malloc fail");
			return (true);
		}
	}
	if (i == 0 || tmp[i - 1] != '\\')
	{
		*str = rewrite_string(data, tmp, i);
		return (true);
	}
	return (false);
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
			if (expand_more(data, tmp, str, i) == true)
			{
				expand_dollar(data, str);
				return ;
			}
		}
		edit_quotes(&single_q, &double_q, &tmp[i]);
		i++;
	}
}
