/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 17:00:20 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/05 16:50:14 by vvan-der      ########   odam.nl         */
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
	j = ft_strlen(s1);
	if (j > 0)
		j--;
	while (ft_strchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}

char	*ft_strtrim2(t_data *data, char *s1, char *set)
{
	int	i;

	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	i = ft_strlen(s1);
	if (i == 0)
		return (mini_shubstr(data, s1, 0));
	while (i > 0 && ft_strchr(set, s1[i - 1]) != NULL)
		i--;
	return (mini_shubstr(data, s1, i));
}
