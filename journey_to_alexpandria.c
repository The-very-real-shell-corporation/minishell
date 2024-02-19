/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   journey_to_alexpandria.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 17:39:28 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 18:12:47 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	contains_one_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	if (str[i] == ' ' && str[i + 1] != '\0')
		return (false);
	return (true);
}

void	journey_to_alexpandria(t_data *data, t_mlist **in, char *str)
{
	int		i;
	char	**arr;
	t_mlist	*tmp;

	i = 0;
	tmp = *in;
	if (ft_strchr(str, '\"') != NULL || ft_strchr(str, '\'') != NULL)
		return ;
	if (contains_one_word((*in)->str) == false)
	{
		arr = ft_split(str, ' ');
		if (arr == NULL)
			exit_error(data, "ft_split failed");
		while (arr[i] != NULL)
		{
			insert_node(*in, (*in)->nx, new_node(data, arr[i], NULL, INIT));
			*in = (*in)->nx;
			i++;
		}
		if (tmp->pv == NULL)
			data->input = data->input->nx;
		unlink_node(tmp);
		free(arr);
	}
}
