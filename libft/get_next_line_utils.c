/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 17:31:07 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/30 14:35:21 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_realloc_gnl(char *old, size_t size)
{
	char	*new;
	size_t	i;

	i = 0;
	if (size == 0)
		return (free(old), NULL);
	new = malloc(size * sizeof(char));
	if (new == NULL)
		return (free(old), NULL);
	if (old != NULL)
	{
		while (old[i] != '\0')
		{
			new[i] = old[i];
			i++;
		}
	}
	free(old);
	new[i] = '\0';
	return (new);
}

int	find_newl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

size_t	get_next_length(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	copy_paste(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\n' && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*combine_strings(t_gnldata *data, char *line, char *buffer)
{
	size_t	i;
	size_t	j;

	i = get_next_length(line);
	j = get_next_length(buffer);
	data->len += j;
	if (data->len + 1 >= data->size)
	{
		data->size *= 2;
		line = ft_realloc_gnl(line, data->size * sizeof(char));
		if (line == NULL)
			return (NULL);
	}
	copy_paste(&line[i], buffer);
	return (line);
}
