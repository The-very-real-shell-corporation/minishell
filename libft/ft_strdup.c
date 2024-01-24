/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 19:36:15 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/24 12:25:53 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*s2;

	s2 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_strcpy(s2, s1);
	return (s2);
}

char	*ft_strdup2(t_data *data, char *s1)
{
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	s2 = ft_calloc2(data, (ft_strlen(s1) + 1), sizeof(char));
	ft_strcpy(s2, s1);
	return (s2);
}
