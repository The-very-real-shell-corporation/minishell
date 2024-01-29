/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/29 21:52:55 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_briefly(void)
{
	int	i;

	i = 0;
	while (i < 500000)
		i++;
}

static void	close_heredoc_fds(int pipe_fds[2][2])
{
	if (pipe_fds[0][0] != -1)
		close(pipe_fds[0][0]);
	if (pipe_fds[0][1] != -1)
		close(pipe_fds[0][1]);
	if (pipe_fds[1][0] != -1)
		close(pipe_fds[1][0]);
	if (pipe_fds[1][1] != -1)
		close(pipe_fds[1][1]);
}

static int	open_heredoc(t_data *data)
{
	int	fd;

	fd = open(HD_PATH, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

void	whatsup_doc(t_data *data, char *delim)
{
	int		fd;
	bool	expansion;
	char	*line;
	pid_t	id;

	id = create_fork(data);
	if (id == 0)
	{
		fd = open_heredoc(data);
		expansion = true;
		if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
			expansion = false;
		wait_briefly();
		while (INFINITY)
		{
			line = readline("> ");
			if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			{
				free(line);
				close(fd);
				close_heredoc_fds(data->pipe_fds);
				exit(EXIT_SUCCESS);
			}
			if (expansion == true)
				expand_dollar(data, &line);
			ft_putendl_fd(line, fd);
			free(line);
		}
	}
	wait_for_process(data, id, NULL);
}
