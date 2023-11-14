/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 17:00:20 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/14 14:34:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(&s1[i]) - 1;
	while (s1[j] != '\0' && ft_strchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j));
}
