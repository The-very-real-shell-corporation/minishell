/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ministrncmp.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 18:27:51 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/23 15:30:49 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ministrncmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str1[i] != '=' && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
