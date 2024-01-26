/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/26 16:25:50 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_fd(t_data *data, int position)
{
	if (position == START)
		return (data->pipe_fds[0][1]);
	else
		return (data->pipe_fds[1][1]);
}

int	heredoc_pos(t_mlist *pipeline)
{
	int	position;

	if (pipeline->pv == NULL)
		position = START;
	else if (pipeline->nx == NULL)
		position = END;
	else
		position = MIDDLE;
	return (position);
}

void	open_heredoc(t_data *data, t_mlist *pipeline)
{
	int	fd;

	open_pipe(data, heredoc_pos(pipeline));
	close(data->pipe_fds[0][1]);
	fd = open("heredoc_dir/heredoc.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	data->pipe_fds[0][1] = fd;
}

void	whatsup_doc(t_data *data, char *delim, int position)
{
	int		fd;
	bool	expansion;
	char	*line;

	(void)position;
	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	fd = heredoc_fd(data, position);
	while (INFINITY)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			break ;
		if (expansion == true)
			expand_dollar(data, &line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	// close(fd);
	direct_pipes_left(data, data->pipe_fds);
	exit(EXIT_SUCCESS);
}

/*	To do: implement signals so interrupting heredoc doesn't close minishell 
and make sure ctrl + D works (EOF)	*/
