/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/02 17:35:20 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Change O_APPEND to O_TRUNC if you prefer heredoc to behave like bash	*/

static int	open_heredoc(t_data *data)
{
	int	fd;

	fd = open(HD_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

static void	wait_briefly()
{
	int	i;

	i = 0;
	while (i < 1000000)
		i++;
}

static void	get_user_input(t_data *data, int fd, char *delim, bool expansion)
{
	char	*line;

	wait_briefly();
	while (INFINITY)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			if (line == NULL)
				ft_putendl_fd("warning: ended heredoc without delimiter", STDERR_FILENO);
			free(line);
			close(fd);
			return ;
		}
		if (expansion == true)
			expand_dollar(data, &line);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	whatsup_doc(t_data *data, char *delim)
{
	int		fd;
	bool	expansion;

	fd = open_heredoc(data);
	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	get_user_input(data, fd, delim, expansion);
}
