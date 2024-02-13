/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 18:42:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/13 17:17:25 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_string(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) == true)
		i++;
	if (str[i] != '\0' && ft_isdigit(str[i]) == false)
		return (-1);
	return (0);
}

static int	mini_to_i(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (check_string(str) == -1)
		return (-1);
	while (str[i] != '\0')
	{
		res *= 10;
		res += (str[i] - '0');
		if (res > INT_MAX)
		{
			ft_putendl_fd("Atoi error: number too large", 2);
			return (-2);
		}
		i++;
	}
	return ((int)res);
}

static int	receive_status(char **args)
{
	int	status;

	status = mini_to_i(*args);
	if (status == -1)
	{
		ft_putendl_fd("error: non-numerical input for exit", STDERR_FILENO);
		return (-1);
	}
	if (status == -2)
		return (-1);
	if (*(args + 1) != NULL)
	{
		ft_putendl_fd("error, multiple arguments for exit", STDERR_FILENO);
		return (-1);
	}
	return (status);
}

int	exit_builtin(t_data *data, char **args)
{
	int	status;

	if (args == NULL || *args == NULL)
		exit(EXIT_SUCCESS);
	status = receive_status(args);
	if (status == -1)
		return (-1);
	ft_putendl_fd("exit", STDOUT_FILENO);
	clean_up(data);
	exit(status);
}
