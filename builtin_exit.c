/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 20:42:04 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_builtin(t_data *data, char **args)
{
	if (args != NULL)
		return (0);
	ft_putendl_fd("exit", STDOUT_FILENO);
	clean_up(data);
	exit(EXIT_SUCCESS);
}