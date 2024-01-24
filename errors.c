/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 11:56:43 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/24 12:06:33 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	lexer_error(t_data *data, char *msg)
{
	ft_putstr_fd("error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	clear_mlist(&data->input);
}