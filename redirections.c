/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/31 18:45:22 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	append_output(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][1]);
	fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == ERROR)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		return (ERROR);
	}
	data->pipe_fds[0][1] = fd;
	return (SUCCESS);
}

static bool	redirect_output(t_data *data, char *pathname)
{
	int		fd;

	close(data->pipe_fds[0][1]);
	fd = open(pathname, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
	}
	data->pipe_fds[0][1] = fd;
	return (SUCCESS);
}

static int	redirect_input(t_data *data, char *pathname)
{
	int	fd;

	close(data->pipe_fds[0][0]);
	fd = open(pathname, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		return (ERROR);
	}
	data->pipe_fds[0][0] = fd;
	return (SUCCESS);
}

bool	setup_redirection(t_data *data, t_mlist *pipeline)
{
	if (pipeline->token != HEREDOC)
		pipeline = pipeline->nx;
	if (pipeline != NULL && pipeline->nx != NULL)
	{
		if (pipeline->token == HEREDOC)
			whatsup_doc(data, pipeline->args[0]);
		if ((pipeline->pv != NULL && pipeline->pv->pv == NULL) || \
			(pipeline->token == HEREDOC && pipeline->pv == NULL))
			open_pipe(data, START);
		else
			open_pipe(data, MIDDLE);
		if (pipeline->token == HEREDOC)
			pipeline->token = RE_INPUT;
		if (pipeline->token == APPEND)
			if (append_output(data, pipeline->nx->args[0]) == ERROR)
				return (ERROR);
		if (pipeline->token == RE_OUTPUT)
			if (redirect_output(data, pipeline->nx->args[0]) == ERROR)
				return (ERROR);
		if (pipeline->token == RE_INPUT)
			if (redirect_input(data, pipeline->nx->args[0]) == ERROR)
				return (ERROR);
	}
	else
		open_pipe(data, END);
	return (SUCCESS);
}
