/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:00:07 by vvan-der          #+#    #+#             */
/*   Updated: 2022/11/15 16:14:06 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < (n - 1))
		i++;
	if (s1[i] != s2[i])
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	return (0);
}
