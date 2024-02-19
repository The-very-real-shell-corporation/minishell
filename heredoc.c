/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 17:31:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Change O_APPEND to O_TRUNC if you prefer heredoc to behave like bash	*/

static int	open_heredoc(t_data *data)
{
	int	fd;

	fd = open(HD_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to create heredoc file (does /tmp exist?)");
	return (fd);
}

static void	get_user_input(int fd, char *delim)
{
	char	*line;

	while (INFINITY)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			if (line == NULL)
			{
				ft_putstr_fd("warning: ended heredoc", STDERR_FILENO);
				ft_putendl_fd(" without delimiter", STDERR_FILENO);
			}
			free(line);
			close(fd);
			return ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	whatsup_doc(t_data *data, char *delim)
{
	int		fd;

	fd = open_heredoc(data);
	get_user_input(fd, delim);
}
