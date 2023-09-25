/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:11:05 by vvan-der          #+#    #+#             */
/*   Updated: 2022/11/14 18:08:58 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (needle[b] == '\0')
		return ((char *)haystack);
	while (haystack[a] && a < len)
	{
		while (haystack[a] && haystack[a] == needle[b] && a < len)
		{
			a++;
			b++;
			if (needle[b] == '\0')
				return ((char *)(&haystack[a - b]));
		}
		a -= b;
		a++;
		b = 0;
	}
	return (NULL);
}
