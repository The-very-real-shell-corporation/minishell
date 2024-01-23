/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/23 16:12:03 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_output(t_data *data, char *pathname)
{
	int	fd;

	printf("pathname: %s\n", pathname);
	fd = open(pathname, O_WRONLY | 00777 | O_CREAT, O_APPEND);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

int	redirect_output(t_data *data, char *pathname)
{
	int	fd;

	printf("pathname: %s\n", pathname);
	fd = open(pathname, O_RDWR);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

int	redirect_input(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_RDWR);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

void	setup_redirection(t_data *data, t_mlist *pipeline)
{
	static int i = 0;

	printf("iteration: %d\n", i);
	print_list(pipeline);
	if (pipeline->nx != NULL)
	{
		if (pipeline->token == APPEND)
			data->pipe_fds[0][1] = append_output(data, pipeline->args[0]);
		if (pipeline->token == RE_OUTPUT)
			data->pipe_fds[0][1] = redirect_output(data, pipeline->args[0]);
		if (pipeline->token == RE_INPUT)
			data->pipe_fds[0][0] = redirect_input(data, pipeline->args[0]);
		if (pipeline->pv->pv == NULL)
			open_pipe(data, START);
		else
			open_pipe(data, MIDDLE);
	}
	else
		open_pipe(data, END);
	i++;
}
