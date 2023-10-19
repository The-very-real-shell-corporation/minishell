/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 19:47:55 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/19 16:47:15 by vvan-der      ########   odam.nl         */
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
	if (ft_strncmp(str, list->str, ft_strlen(str) + 1) < 0)
	{
		*direction = LEFT;
		while (list->pv != NULL && \
		ft_strncmp(str, list->pv->str, ft_strlen(str) + 1) < 0)
			list = list->pv;
		return (list);
	}
	else if (ft_strncmp(str, list->str, ft_strlen(str) + 1) > 0)
	{
		*direction = RIGHT;
		while (list->nx != NULL && \
		ft_strncmp(str, list->nx->str, ft_strlen(str) + 1) > 0)
			list = list->nx;
	}
	return (list);
}

void	sort_environment(t_data *data)
{
	t_mlist	*tmp;
	t_mlist	*tmp2;
	bool	direction;

	tmp2 = data->env;
	direction = LEFT;
	if (data->env == NULL)
		return ;
	tmp = new_node(data, data->env->str);
	data->env = data->env->nx;
	while (data->env != NULL)
	{
		tmp = find_position(data->env->str, tmp, &direction);
		if (direction == LEFT)
			insert_node(&tmp->pv, &tmp, new_node(data, data->env->str));
		else
			insert_node(&tmp, &tmp->nx, new_node(data, data->env->str));
		data->env = data->env->nx;
	}
	data->sorted_env = node_first(tmp);
	data->env = tmp2;
}

void	copy_environment(t_data *data, char **envp)
{
	int	i;
	t_mlist	*tmp;

	i = 0;
	if (envp == NULL)
		exit_error(data, "Envp was NULL somehow");
	tmp = NULL;
	while (envp[i] != NULL)
	{
		node_addback(&tmp, new_node(data, envp[i]));
		i++;
	}
	data->env = tmp;
}
