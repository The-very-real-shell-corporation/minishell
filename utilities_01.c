/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 13:50:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 18:48:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array(t_data *data, t_mlist *input)
{
	char	**arr;
	size_t	i;

	i = 0;
	arr = ft_calloc2(data, (list_size_redirection(input) + 1), sizeof(char *));
	while (input != NULL && is_redirection(input->token) == false)
	{
		arr[i] = ft_strdup2(data, input->str);
		input = input->nx;
		i++;
	}
	if (*arr == NULL)
		return (free(arr), NULL);
	return (arr);
}

bool	is_builtin(t_token tolkien)
{
	if (tolkien >= B_CD && tolkien <= B_UNSET)
		return (true);
	return (false);
}

bool	is_redirection(t_token tolkien)
{
	if (tolkien >= APPEND && tolkien <= RE_INPUT)
		return (true);
	return (false);
}

bool	everythingiswhitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_iswhitespace(str[i]) == true)
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}
