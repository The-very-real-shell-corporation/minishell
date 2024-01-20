/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/20 15:32:46 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_output(t_data *data, char *pathname, char *output)
{
	int	fd;

	fd = open(pathname, O_WRONLY, O_CREAT, O_APPEND);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	ft_putstr_fd(output, fd);
	close(fd);
}

void	redirect_output(t_data *data, char *pathname, char *output)
{
	int	fd;

	fd = open(pathname, O_WRONLY, O_CREAT);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	ft_putstr_fd(output, fd);
	close(fd);
}
