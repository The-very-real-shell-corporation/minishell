/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/23 20:44:10 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_output(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][1]);
	fd = open(pathname, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

int	redirect_output(t_data *data, char *pathname)
{
	int		fd;

	close(data->pipe_fds[0][1]);
	fd = open(pathname, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

int	redirect_input(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][0]);
	fd = open(pathname, O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

void	setup_redirection(t_data *data, t_mlist *pipeline)
{
	if (pipeline->nx != NULL)
	{
		if (pipeline->pv->pv == NULL)
			open_pipe(data, START);
		else
			open_pipe(data, MIDDLE);
		if (pipeline->token == APPEND)
			data->pipe_fds[0][1] = append_output(data, pipeline->nx->args[0]);
		if (pipeline->token == RE_OUTPUT)
			data->pipe_fds[0][1] = redirect_output(data, pipeline->nx->args[0]);
		if (pipeline->token == RE_INPUT)
			data->pipe_fds[0][0] = redirect_input(data, pipeline->nx->args[0]);
	}
	else
		open_pipe(data, END);
}
