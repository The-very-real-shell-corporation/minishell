/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 19:47:55 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/05 22:47:41 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (list);
	}
	return (list);
}

void	sort_environment(t_data *data)
{
	t_mlist	*tmp;
	t_mlist	*tmp2;
	bool	direction;

	if (data->env == NULL)
		return ;
	tmp2 = node_first(data->env);
	tmp = new_node(data, ft_strdup2(data, data->env->str));
	data->env = data->env->nx;
	direction = LEFT;
	while (data->env != NULL)
	{
		tmp = find_position(data->env->str, tmp, &direction);
		if (direction == LEFT)
			insert_node(tmp->pv, tmp, new_node(data, ft_strdup2(data, data->env->str)));
		else if (direction == RIGHT)
			insert_node(tmp, tmp->nx, new_node(data, ft_strdup2(data, data->env->str)));
		data->env = data->env->nx;
		print_list((node_first(tmp)));
	}
	data->sorted_env = node_first(tmp);
	data->env = tmp2;
}

void	copy_environment(t_data *data, char **envp)
{
	int		i;
	t_mlist	*tmp;

	i = 0;
	if (envp == NULL)
		exit_error(data, "Envp was NULL somehow");
	tmp = NULL;
	while (envp[i] != NULL)
	{
		node_addback(&tmp, new_node(data, ft_strdup2(data, envp[i])));
		i++;
	}
	data->env = tmp;
}

void	change_env_var(t_data *data, char *var, char *new_value)
{
	t_mlist	*tmp;
	char	*temp;

	tmp = find_input(data->env, var);
	if (tmp != NULL)
	{
		temp = tmp->str;
		tmp->str = ft_strjoin(var, new_value);
		free(temp);
	}
	free(new_value);
}
