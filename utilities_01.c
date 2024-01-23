/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 13:50:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/23 15:05:58 by vvan-der      ########   odam.nl         */
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
	char	**arr;
	char	*tmp;
	size_t	i;

	i = 0;
	arr = ft_calloc2(data, (list_size_redirection(input) + 1), sizeof(char *));
	while (input != NULL && is_redirection(input->token) == NONE)
	{
		arr[i] = ft_strdup2(data, input->str);
		tmp = arr[i];
		arr[i] = ft_strtrim2(data, tmp, " ");
		free(tmp);
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

int	is_redirection(t_token tolkien)
{
	if (tolkien >= APPEND && tolkien <= RE_OUTPUT)
		return (RIGHT);
	if (tolkien >= HEREDOC && tolkien <= RE_INPUT)
		return (LEFT);
	return (NONE);
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
