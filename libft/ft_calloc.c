/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 13:27:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 18:33:14 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (count * size));
	return ((void *)str);
}

void	*ft_calloc2(t_data *data, size_t count, size_t size)
{
	char	*str;

	str = malloc(count * size);
	if (str == NULL)
		exit_error(data, "ft_calloc failed");
	ft_bzero(str, (count * size));
	return ((void *)str);
}
