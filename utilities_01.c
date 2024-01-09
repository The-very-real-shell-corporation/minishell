/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 13:50:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/09 19:09:07 by vvan-der      ########   odam.nl         */
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

char	**list_to_array(t_data *data, t_mlist *input)
{
	char 	**result;
	char	*tmp;
	size_t	i;

	result = ft_calloc((list_size(input) + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (input != NULL)
	{
		result[i] = ft_strdup2(data, input->str);
		tmp = result[i];
		result[i] = ft_strtrim(tmp, " ");
		free(tmp);
		input = input->nx;
		i++;
	}
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