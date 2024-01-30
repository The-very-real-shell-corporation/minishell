/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 18:43:27 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_data *data, char **args)
{
	bool	n_flag;

	if (*args == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	(void)data;
	n_flag = false;
	if (ft_strncmp("-n", *args, 3) == 0)
	{
		n_flag = true;
		args++;
	}
	while (*args != NULL)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1) != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		args++;
	}
	if (n_flag == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
