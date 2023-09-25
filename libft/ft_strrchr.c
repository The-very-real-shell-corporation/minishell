/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:28:41 by vvan-der          #+#    #+#             */
/*   Updated: 2023/03/10 16:16:33 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char) c == '\0')
		return ((char *) &s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
	}
	return (NULL);
}
