/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:23:43 by vvan-der          #+#    #+#             */
/*   Updated: 2023/03/10 15:40:43 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	if (dst == src)
		return (dst);
	while (i < len && dst != src)
	{
		if (dst < src)
		{
			((char *) dst)[i] = ((char *) src)[i];
			i++;
		}
		if (dst > src)
		{
			i++;
			((char *) dst)[len - i] = ((char *) src)[len - i];
		}
	}
	return (dst);
}
