/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 13:50:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/20 17:01:20 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_2d_charray(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("String [%d]: %s\n", i, array[i]);
		i++;
	}
	printf("String [%d]: %s\n", i, array[i]);
}

char	**list_to_array(t_data *data, t_mlist *input, t_token tolkien)
{
	char	**result;
	char	*tmp;
	size_t	i;

	result = ft_calloc2(data, (list_size(input, tolkien) + 1), sizeof(char *));
	i = 0;
	while (input != NULL && input->token != tolkien)
	{
		result[i] = ft_strdup2(data, input->str);
		tmp = result[i];
		result[i] = ft_strtrim2(data, tmp, " ");
		free(tmp);
		input = input->nx;
		i++;
	}
	if (*result == NULL)
		return (free(result), NULL);
	return (result);
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
