/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/06 15:15:01 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/16 20:13:20 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s3;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	s3 = malloc((i + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	ft_strcpy(s3, (char *)s1);
	ft_strcpy(&s3[i], (char *)s2);
	return (s3);
}

char	*ft_strjoin2(t_data *data, char *s1, char *s2)
{
	char	*s3;
	size_t	i;

	i = ft_strlen(s1);
	s3 = malloc((i + ft_strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
	{
		free(s1);
		free(s2);
		exit_error(data, "strjoin failed");
	}
	ft_strcpy(s3, s1);
	ft_strcpy(&s3[i], s2);
	return (s3);
}
