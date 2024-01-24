/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/24 16:03:50 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_output(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][1]);
	fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	data->pipe_fds[0][1] = fd;
}

static void	redirect_output(t_data *data, char *pathname)
{
	int		fd;

	close(data->pipe_fds[0][1]);
	fd = open(pathname, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	data->pipe_fds[0][1] = fd;
}

static void	redirect_input(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][0]);
	fd = open(pathname, O_RDONLY, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	data->pipe_fds[0][0] = fd;
}

static void	open_heredoc(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][0]);
	fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	data->pipe_fds[0][0] = fd;
}

void	setup_redirection(t_data *data, t_mlist *pipeline)
{
	if (pipeline->token == HEREDOC)
	{
		open_pipe(data, END);
		open_heredoc(data, "heredoc_dir/heredoc.txt");
		return ;
	}
	pipeline = pipeline->nx;
	if (pipeline->nx != NULL)
	{
		if (pipeline->pv->pv == NULL)
			open_pipe(data, START);
		else
			open_pipe(data, MIDDLE);
		if (pipeline->token == APPEND)
			append_output(data, pipeline->nx->args[0]);
		if (pipeline->token == RE_OUTPUT)
			redirect_output(data, pipeline->nx->args[0]);
		if (pipeline->token == RE_INPUT)
			redirect_input(data, pipeline->nx->args[0]);
		if (pipeline->token == HEREDOC)
			open_heredoc(data, "heredoc_dir/heredoc.txt");
	}
	else
	{
		puts("WHOOP");
		open_pipe(data, END);
	}
}
