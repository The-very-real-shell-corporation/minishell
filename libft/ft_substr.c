/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:38:56 by vvan-der          #+#    #+#             */
/*   Updated: 2022/11/15 17:00:04 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	while (*s && i < start)
	{
		s++;
		i++;
	}
	if (ft_strlen(s) < len)
	{
		sub = malloc((ft_strlen(s) + 1) * sizeof(char));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, s, ft_strlen(s) + 1);
	}
	else
	{
		sub = malloc((len + 1) * sizeof(char));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, s, len + 1);
	}
	return (sub);
}
