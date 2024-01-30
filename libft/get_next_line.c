/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/14 17:28:35 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/30 14:39:55 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	manage_buffer(char *dest, char *src)
{
	size_t	i;

	i = 0;
	if (find_newl(dest) == NOT_FOUND)
	{
		dest[0] = '\0';
		return ;
	}
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	*read_stuff(t_gnldata *data, int fd, char *line, char *buffer)
{
	int		bytes_read;

	bytes_read = 1;
	line = combine_strings(data, line, buffer);
	if (line == NULL)
		return (NULL);
	data->len = get_next_length(line);
	while (find_newl(buffer) == NOT_FOUND && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			buffer[0] = '\0';
			return (free(line), NULL);
		}
		buffer[bytes_read] = '\0';
		line = combine_strings(data, line, buffer);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_gnldata	data;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	data.size = BUFFER_SIZE + 1;
	data.len = BUFFER_SIZE;
	data.line = read_stuff(&data, fd, NULL, buffer);
	if (data.line == NULL)
		return (NULL);
	manage_buffer(buffer, &buffer[find_newl(buffer) + 1]);
	data.line = ft_realloc_gnl(data.line, get_next_length(data.line) + 1);
	if (data.line == NULL)
		return (NULL);
	if (*data.line == '\0')
		return (free(data.line), NULL);
	return (data.line);
}
