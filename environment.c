/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 19:47:55 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 18:37:03 by vincent       ########   odam.nl         */
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

t_mlist	*sort_environment(t_data *data, t_mlist *env)
{
	t_mlist	*sorted;
	bool	direction;

	if (env == NULL)
		return (NULL);
	sorted = new_node(data, ft_strdup2(data, env->str), NULL, INITIALIZED);
	env = env->nx;
	direction = LEFT;
	while (env != NULL)
	{
		sorted = find_position(env->str, sorted, &direction);
		if (direction == LEFT)
			insert_node(sorted->pv, sorted, \
			new_node(data, ft_strdup2(data, env->str), NULL, INITIALIZED));
		else if (direction == RIGHT)
			insert_node(sorted, sorted->nx, \
			new_node(data, ft_strdup2(data, env->str), NULL, INITIALIZED));
		env = env->nx;
	}
	return (node_first(sorted));
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
		node_addback(&tmp, new_node(data, \
		ft_strdup2(data, envp[i]), NULL, INITIALIZED));
		i++;
	}
	data->env = tmp;
}

void	change_env_var(t_data *data, char *var, char *new_value)
{
	t_mlist	*tmp;

	tmp = find_input(data->env, var);
	if (tmp != NULL)
	{
		free(tmp->str);
		tmp->str = ft_strjoin2(data, var, new_value);
	}
	free(new_value);
}
