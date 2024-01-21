/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/21 17:00:31 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_output(t_data *data, char *pathname) // bend pipes instead?
{
	int	fd;

	fd = open(pathname, O_RDWR, O_CREAT, O_APPEND);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}

int	redirect_output(t_data *data, char *pathname) // bend pipes instead?
{
	int	fd;

	fd = open(pathname, O_RDWR, O_CREAT);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	return (fd);
}
