/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 15:20:52 by vvan-der      #+#    #+#                 */
/*   Updated: 2022/11/06 15:21:39 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*d;

	d = b;
	i = 0;
	while (i < len)
	{
		d[i] = c;
		i++;
	}
	return (b);
}
