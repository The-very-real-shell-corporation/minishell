/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:00:20 by vvan-der          #+#    #+#             */
/*   Updated: 2023/07/22 14:32:47 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*tmp;
	char	*trim;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	tmp = ft_strdup(s1);
	if (tmp == NULL)
		return (NULL);
	if (*tmp == '\0')
		return (tmp);
	trim = tmp;
	tmp += ft_strlen(tmp) - 1;
	while (ft_strchr(set, *tmp))
		tmp--;
	*(++tmp) = '\0';
	tmp = trim;
	trim = ft_strdup(trim);
	free(tmp);
	return (trim);
}
