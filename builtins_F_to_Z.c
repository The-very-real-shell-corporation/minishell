/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_F_to_Z.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 16:35:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/30 15:42:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(t_data *data, char **args)
{
	char	*out;

	(void)args;
	out = getcwd(NULL, 0);
	if (out == NULL)
		exit_error(data, "cwd failed\n");
	ft_putendl_fd(out, STDOUT_FILENO);
	free(out);
	return (0);
}

int	unset_builtin(t_data *data, char **args)
{
	t_mlist	*tmp;

	if (*args == NULL)
	{
		printf("Please provide a variable to unset\n");
		return (0);
	}
	while (*args != NULL)
	{
		if (ft_strchr(*args, '=') == NULL)
		{
			tmp = find_input(data->env, *args);
			if (tmp != NULL)
				unlink_node(tmp);
		}
		args++;
	}
	return (0);
}
