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
		return (NULL);
	original[start] = '\0';
	ft_strcpy(new, original);
	ft_strcpy(&new[start], newpart);
	ft_strcpy(&new[start + newpart_len], &original[start + len]);
	free(original);
	free(newpart);
	return (new);
}
