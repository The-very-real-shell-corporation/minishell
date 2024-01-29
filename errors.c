/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 11:56:43 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/29 20:54:14 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	unlink(HD_PATH);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	lexer_error(t_data *data, char *msg, char *token)
{
	// ft_putstr_fd("error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\"", 1);
	ft_putstr_fd(token, STDERR_FILENO);
	write(STDERR_FILENO, "\"\n", 2);	
	clear_mlist(&data->input);
}
