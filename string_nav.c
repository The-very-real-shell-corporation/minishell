/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_nav.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 15:53:40 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 15:35:34 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	first_last(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (true);
	return (false);
}

int	ft_ministrcmp(char *env_str, char *input)
{
	size_t	i;

	i = 0;
	while (env_str[i] != '\0' && env_str[i] != '=' && env_str[i] == input[i])
		i++;
	if ((env_str[i] == '=' && input[i] == '\0') || \
		(env_str[i] == '\0' && input[i] == '='))
		i--;
	if (input[i] != '\0' && input[i + 1] != '\0')
		return (-1);
	return (env_str[i] - input[i]);
}

int	ptr_array_size(void **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
