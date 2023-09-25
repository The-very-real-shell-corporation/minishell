/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 11:19:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 15:40:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, size_t size)
{
	char	*new_str;

	new_str = ft_calloc(size, sizeof(char));
	if (new_str == NULL)
		exit(EXIT_FAILURE);
	if (str != NULL)
		ft_strcpy(new_str, str);
	free(str);
	return (new_str);
}
