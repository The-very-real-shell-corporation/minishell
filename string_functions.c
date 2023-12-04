/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ministrcmp.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 18:27:51 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/23 15:30:49 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_string(t_data *data, char *input)
{
	char	*value;
	t_mlist	*tmp;
	char	*str;

	str = ft_strjoin(input, "=");
	tmp = find_input(data->env, str);
	free(str);
	if (tmp == NULL)
		str = "";
	else
		str = tmp->str;
	while (*str != '\0' && *str != '=')
		str++;
	if (*str == '=')
		str++;
	value = ft_strdup2(data, str);
	return (value);
}

char	*partially_merge_str(char *original, int start, int len, char *newpart)
{
	char	*new;
	int		newpart_len;

	newpart_len = ft_strlen(newpart);
	new = ft_calloc(ft_strlen(original) - len + newpart_len + 1, sizeof(char));
	if (new == NULL)
	{
		free(original);
		free(newpart);
		return (NULL);
	}
	original[start] = '\0';
	ft_strcpy(new, original);
	ft_strcpy(&new[start], newpart);
	ft_strcpy(&new[start + newpart_len], &original[start + len]);
	free(original);
	free(newpart);
	return (new);
}

char	*mini_shubstr(t_data *data, char *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((len + 1), sizeof(char));
	if (word == NULL)
		exit_error(data, "Malloc error");
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

void	dollar_in_env(t_data *data, char *input, char **env_string)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = 1;
	tmp = ft_strchr(input, '=');
	if (tmp != NULL && ft_strchr(input, '$') != NULL && ft_strchr(input, '$') < tmp)
		*env_string = NULL;
	else if (tmp != NULL && ft_strchr(tmp, '$') != NULL)
	{
		tmp2 = ft_strdup2(data, input);
		while (tmp2[i] != '\0')
		{
			if (tmp2[i] == '$' && tmp2[i - 1] != '\\')
				break ;
			i++;
		}
		if (tmp2[i] == '\0')
			return (free(tmp2));
		*env_string = partially_merge_str(tmp2, i, 1, ft_strdup2(data, "\\$"));
		dollar_in_env(data, *env_string, env_string);
	}
}
