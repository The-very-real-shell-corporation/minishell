/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 18:33:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/02/14 20:33:50 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_access(char *filename, int *status)
{
	*status = 0;
	if (access(filename, F_OK) == -1)
	{
		*status = 126;
		return (ERROR);
	}
	if (access(filename, X_OK) == -1)
	{
		*status = 127;
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(": insufficient permissions", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	loop_through_path(t_data *data, t_mlist *p, char **path, char *cwd)
{
	int		i;
	int		status;
	char	*directory;

	i = 0;
	status = 0;
	while (path != NULL && path[i] != NULL)
	{
		chdir(path[i]);
		if (check_access(p->args[0], &status) == SUCCESS)
		{
			directory = ft_strjoin2(data, data->real_path[i], p->args[0]);
			chdir(cwd);
			execute_command(data, directory, p->args);
		}
		if (status == 127)
			break ;
		i++;
	}
	chdir(cwd);
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
	status = loop_through_path(data, p, path, cwd);
	if (status != 127 && check_access(p->args[0], &status) == SUCCESS)
		execute_command(data, ft_strdup2(data, p->args[0]), p->args);
	if (status == 126)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(p->args[0], STDERR_FILENO);
	}
	clean_up(data);
	exit(status);
}

void	execute_command(t_data *data, char *directory, char **args)
{
	if (execve(directory, args, data->env_array) == -1)
	{
		free(directory);
		exit_error(data, "execve failed");
	}
	free(directory);
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
