/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:21 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/14 18:44:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_new_directory(t_data *data, char *tmp)
{
	if (errno == 0)
		change_env_var(data, "OLDPWD=", tmp);
	tmp = getcwd(NULL, 0);
	if (check_errno(&data->exit_status) == ERROR)
		return (data->exit_status);
	if (tmp == NULL)
		exit_error(data, "getcwd failed");
	change_env_var(data, "PWD=", tmp);
	return (EXIT_SUCCESS);
}

static char	*check_old_directory(t_data *data)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (errno == ENOENT)
	{
		change_env_var(data, "PWD=", ft_strdup2(data, ""));
	}
	else if (tmp == NULL)
		exit_error(data, "getcwd malloc failed");
	return (tmp);
}

static bool	check_errors(char **args)
{
	if (args == NULL || *args == NULL)
	{
		ft_putendl_fd("no directory specified", STDERR_FILENO);
		return (ERROR);
	}
	if (*(args + 1) != NULL)
	{
		ft_putstr_fd("error: can't navigate to multiple folde", STDERR_FILENO);
		ft_putendl_fd("rs at once, I'm not a quantum computer", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	cd_builtin(t_data *data, char **args)
{
	char	*tmp;

	if (check_errors(args) == ERROR)
		return (EXIT_FAILURE);
	tmp = check_old_directory(data);
	if (chdir(*args) == -1)
	{
		free(tmp);
		ft_putstr_fd("error: ", STDERR_FILENO);
		ft_putstr_fd(*args, STDERR_FILENO);
		ft_putendl_fd(" is not a directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (check_new_directory(data, tmp));
}
