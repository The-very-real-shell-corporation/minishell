/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 14:45:29 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_filename(t_data *data, int *value)
{
	char	*name;
	char	*tmp;

	(data->heredocs)++; // nonsense -> do it in parent
	tmp = ft_itoa2(data, data->heredocs);
	if (tmp == NULL)
	{
		*value = 5;
		return (NULL);
	}
	name = ft_strjoin("shobjects/heredoc", tmp); // bullshit -> do in parent
	if (name == NULL)
	{
		free(tmp);
		*value = 6;
		return (NULL);
	}
	free(tmp);
	return (name);
}

int	doodle_in_doc(t_data *data, int fd, char *delim)
{
	bool	expansion;

	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	free(data->line);
	while (INFINITY)
	{
		data->line = readline("> ");
		if (data->line == NULL)
			return (2);
		if (ft_strncmp(data->line, delim, ft_strlen(delim)) == 0)
			return (0);
		if (expansion == true)
			expand_dollar(data, &data->line);
		write(fd, data->line, ft_strlen(data->line));
		write(fd, "\n", 1);
		free(data->line);
	}
}

void	whatsup_doc(t_data *data, char *delim)
{
	pid_t	id;
	int		value;
	int		fd;
	char	*name;

	value = 0;
	id = create_fork(data);
	if (id == 0)
	{
		name = create_filename(data, &value);
		if (name == NULL)
			exit(value);
		fd = open(name, O_CREAT | O_APPEND | O_RDWR, 00777);
		if (fd == -1)
			value = EXIT_FAILURE;
		else
		{
			value = doodle_in_doc(data, fd, delim);
			close(fd);
		}
		free(name);
		clean_up(data);
		exit(value);
	}
	waitpid(id, &data->exit_status, 0);
	if (WEXITSTATUS(data->exit_status) == EXIT_FAILURE)
		exit_error(data, "heredoc file failed to open");
	if (WEXITSTATUS(data->exit_status) == 2)
		write(STDERR_FILENO, "exited heredoc without delim\n", 30);
	if (WEXITSTATUS(data->exit_status) == 5)
		write(STDERR_FILENO, "itoa failed\n", 13);
	if (WEXITSTATUS(data->exit_status) == 6)
		write(STDERR_FILENO, "strjoin failed\n", 16);
	// else
	// 	write(STDOUT_FILENO, "\n", 1);
}