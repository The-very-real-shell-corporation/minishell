/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 18:33:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/20 23:25:58 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_access(char *filepath, int *status)
{
	*status = 0;
	if (access(filepath, F_OK) == -1)
	{
		*status = 126;
		return (ERROR);
	}
	if (access(filepath, X_OK) == -1)
	{
		*status = 127;
		ft_putstr_fd(filepath, STDERR_FILENO);
		ft_putendl_fd(": insufficient permissions", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	loop_through_path(t_data *data, t_mlist *p, char **path)
{
	int		i;
	int		status;
	char	*filepath;

	i = 0;
	status = 0;
	while (path != NULL && path[i] != NULL && status != 127)
	{
		filepath = ft_strjoin2(data, data->real_path[i], p->args[0]);
		if (check_access(filepath, &status) == SUCCESS)
			execute_command(data, filepath, p->args);
		free(filepath);
		i++;
	}
	return (status);
}

void	execute_through_path(t_data *data, t_mlist *p, char **path)
{
	int		status;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (check_errno(&status, "can't work in the void") == ERROR)
		exit(EXIT_FAILURE);
	if (cwd == NULL)
		exit_error(data, "cwd failed");
	data->env_array = list_to_array(data, data->env);
	status = loop_through_path(data, p, path);
	if (status == 126)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(p->args[0], STDERR_FILENO);
	}
	clean_up(data);
	exit(status);
}

void	execute_command(t_data *data, char *filepath, char **args)
{
	int	status;

	data->env_array = list_to_array(data, data->env);
	if (check_access(filepath, &status) == SUCCESS)
	{
		if (execve(filepath, args, data->env_array) == -1)
			exit_error(data, "execve failed");
	}
	if (status == 126)
	{
		ft_putstr_fd("File or folder doesn't exist: ", STDERR_FILENO);
		ft_putendl_fd(filepath, STDERR_FILENO);
	}
	clean_up(data);
	exit(EXIT_FAILURE);
}

bool	run_builtins(t_data *data, t_mlist *p)
{
	if (is_builtin(p->token) == true)
	{
		data->exit_status = data->fn[p->token](data, &p->args[1]);
		return (true);
	}
	return (false);
}
