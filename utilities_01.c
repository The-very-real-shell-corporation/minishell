/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 13:50:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/28 18:52:37 by akasiota      ########   odam.nl         */
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
	puts("NULL");
}

char	**list_to_array(t_data *data ,t_mlist *list)
{
	char 	**result;
	char	*tmp;
	size_t	i;

	result = ft_calloc((list_size(list) + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (list != NULL)
	{
		result[i] = ft_strdup2(data, list->str);
		tmp = result[i];
		result[i] = ft_strtrim(tmp, " ");
		free(tmp);
		list = list->nx;
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