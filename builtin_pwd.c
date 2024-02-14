/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/14 18:58:32 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_data *data, char **args)
{
	char	*out;

	(void)args;
	out = getcwd(NULL, 0);
	if (errno == ENOENT)
	{
		ft_putendl_fd(strerror(ENOENT), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (out == NULL)
		exit_error(data, "cwd failed");
	ft_putendl_fd(out, STDOUT_FILENO);
	free(out);
	return (EXIT_SUCCESS);
}
