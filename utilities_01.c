/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities_01.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 13:50:27 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/18 14:48:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2D(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	input = NULL;
}

char	**chop_string(char *input)
{
	char	**result;
	char	**tmp;

	result = ft_shell_split(input);
	if (!result)
		exit_error("Split failed");
	tmp = result;
	while (*result)
	{
		printf("%s\n", *result);
		result++;
	}
	result = tmp;
	return (result);
}