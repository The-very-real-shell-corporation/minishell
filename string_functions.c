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

char	*envp_string(t_data *data, char *input)
{
	t_mlist	*tmp;
	char	*str;

	tmp = find_input(data->env, input);
	str = "";
	if (tmp != NULL)
		str = tmp->str;
	while (*str != '\0' && *str != '=')
		str++;
	if (*str == '=')
		str++;
	return (ft_strdup2(data, str));
}

/*	Takes the new part to overwrite a set part of the original string, 
	returning a brand new string with the changes, used in expansion	*/

char	*remake_str(char *original, int start, int len, char *newpart)
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
	word = ft_calloc2(data, len + 1, sizeof(char));
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
	if (tmp != NULL && ft_strchr(input, '$') != NULL \
		&& ft_strchr(input, '$') < tmp)
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
		*env_string = remake_str(tmp2, i, 1, ft_strdup2(data, "\\$"));
		dollar_in_env(data, *env_string, env_string);
	}
}
