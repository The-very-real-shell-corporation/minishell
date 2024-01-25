/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/25 20:59:11 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_heredoc(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][0]);
	fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	data->pipe_fds[0][0] = fd;
}

void	setup_heredoc(t_data *data, t_mlist *pipeline)
{
	if (pipeline->pv == NULL)
		open_pipe(data, START);
	if (pipeline->nx == NULL)
		open_pipe(data, END);
	else
		open_pipe(data, MIDDLE);
	open_heredoc(data, "heredoc_dir/heredoc.txt");
}

void	whatsup_doc(t_data *data, char *delim)
{
	bool	expansion;
	char	*line;

	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	while (INFINITY)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			break ;
		if (expansion == true)
			expand_dollar(data, &line);
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
	free(line);
	exit(EXIT_SUCCESS);
}

/*	To do: implement signals so interrupting heredoc doesn't close minishell 
and make sure ctrl + D works (EOF)	*/
