/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/15 15:45:42 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_output(t_data *data, char *pathname, bool *status)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == ERROR)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		*status = ERROR;
		return ;
	}
	duplicate_fd(data, fd, STDOUT_FILENO);
	*status = SUCCESS;
}

static void	redirect_output(t_data *data, char *pathname, bool *status)
{
	int		fd;

	fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		*status = ERROR;
		return ;
	}
	duplicate_fd(data, fd, STDOUT_FILENO);
	*status = SUCCESS;
}

static void	redirect_input(t_data *data, char *pathname, bool *status)
{
	int	fd;

	fd = open(pathname, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("failed to open file: ", STDERR_FILENO);
		ft_putendl_fd(pathname, STDERR_FILENO);
		*status = ERROR;
		return ;
	}
	duplicate_fd(data, fd, STDIN_FILENO);
	*status = SUCCESS;
}

bool	setup_redirections(t_data *data, t_mlist *pipeline)
{
	bool	status;

	status = SUCCESS;
	while (pipeline != NULL && pipeline->token != PIPE)
	{
		if (pipeline->token == APPEND)
			append_output(data, pipeline->nx->args[0], &status);
		if (pipeline->token == RE_OUTPUT)
			redirect_output(data, pipeline->nx->args[0], &status);
		if (pipeline->token == RE_INPUT)
			redirect_input(data, pipeline->nx->args[0], &status);
		if (pipeline->token == HEREDOC)
		{
			whatsup_doc(data, pipeline->args[0]);
			if (count_tokens(pipeline->nx, HEREDOC) == 0)
				redirect_input(data, HD_PATH, &status);
		}
		if (status == ERROR)
			break ;
		pipeline = pipeline->nx;
	}
	return (status);
}
