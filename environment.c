/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 19:47:55 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/16 21:25:39 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path_ready(t_data *data)
{
	data->path = ft_split(getenv("PATH"), ':');
	if (data->path == NULL)
		exit_error(data, "Split error\n");
}

t_mlist	*find_position(char *str, t_mlist *list, bool *direction)
{
	if (list == NULL)
		puts("DANGER LEVELS");
	if (ft_strncmp(str, list->str, ft_strlen(str) + 1) < 0)
	{
		*direction = LEFT;
		while (list->pv != NULL && \
		ft_strncmp(str, list->pv->str, ft_strlen(str) + 1) < 0)
		{
			// puts("test");
			list = list->pv;
		}
		if (list == NULL)
			puts("DANGER LEVELS");
		return (list);
	}
	else if (ft_strncmp(str, list->str, ft_strlen(str) + 1) > 0)
	{
		*direction = RIGHT;
		while (list->nx != NULL && \
		ft_strncmp(str, list->str, ft_strlen(str) + 1) > 0)
			list = list->nx;
		if (list == NULL)
			puts("DANGER LEVELS");
	}
	return (list);
}

void	sort_environment(t_data *data)
{
	int		i;
	t_mlist	*tmp;
	bool	direction;

	i = 1;
	direction = LEFT;
	if (data->env[0] == NULL)
		return ;
	tmp = new_node(data, data->env[0]);
	printf("sorted_env[0] %s\n", tmp->str);
	while (i < 7 && data->env[i] != NULL)
	{
		printf("env:		%s\n", data->env[i]);
		printf("sortptr:	%s\n", tmp->str);
		print_list(tmp);
		tmp = find_position(data->env[i], tmp, &direction);
		if (direction == LEFT)
		{
			printf("after_ptr:	%s\n", tmp->str);
			insert_node(&tmp->pv, &tmp, new_node(data, data->env[i]));
			puts("left\n\n");
		}
		else
		{
			insert_node(&tmp, &tmp->nx, new_node(data, data->env[i]));
			printf("after_ptr:	%s\n", tmp->str);
			puts("right\n\n");
		}
		i++;
	}
	while (tmp->pv != NULL)
		tmp = tmp->pv;
	data->sorted_env = tmp;
}

void	copy_environment(t_data *data, char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i] != NULL)
		i++;
	data->env = ft_calloc(i + 1, sizeof(char *));
	if (data->env == NULL)
		exit_error(data, "Malloc fail");
	i = 0;
	while (envp[i] != NULL)
	{
		data->env[i] = ft_strdup(envp[i]);
		if (data->env[i] == NULL)
			exit_error(data, "Malloc fail");
		i++;
	}
}
