/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_nav.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 15:53:40 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/20 15:54:41 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	first_last(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (true);
	return (false);
}

int	ft_ministrcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str1[i] != '=' && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
