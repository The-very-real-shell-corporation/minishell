/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 11:19:49 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 18:39:01 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(t_data *data, char *str, size_t size)
{
	char	*new_str;

	new_str = ft_calloc2(data, size, sizeof(char));
	ft_strcpy(new_str, str);
	free(str);
	return (new_str);
}
