/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/02 13:55:54 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	append_output(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == ERROR)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		return (ERROR);
	}
	duplicate_fd(data, fd, STDOUT_FILENO);
	return (SUCCESS);
}

static bool	redirect_output(t_data *data, char *pathname)
{
	int		fd;

	fd = open(pathname, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
	}
	duplicate_fd(data, fd, STDOUT_FILENO);
	return (SUCCESS);
}

static bool	redirect_input(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		return (ERROR);
	}
	duplicate_fd(data, fd, STDIN_FILENO);
	return (SUCCESS);
}

bool	setup_redirection(t_data *data, t_mlist *pipeline)
{
	while (pipeline != NULL && pipeline->token != PIPE)
	{
		if (pipeline->nx != NULL)
		{
			if (pipeline->token == APPEND)
				append_output(data, pipeline->nx->args[0]);
			if (pipeline->token == RE_OUTPUT)
				append_output(data, pipeline->nx->args[0]);
			if (pipeline->token == RE_INPUT)
				append_output(data, pipeline->nx->args[0]);
		}
		pipeline = pipeline->nx;
	}
	return (SUCCESS);
}
