/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexpander.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:27:05 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/14 17:30:22 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*variable_to_value(t_data *data, char **var)
{
	char	*value;

	
} */

/* void	trim_n_free(t_data *data, t_mlist *node, char *c)
{
	char	*tmp;

	tmp = node->str;
	node->str = ft_strtrim(tmp, c);
	if (node->str == NULL)
		exit_error(data, "Malloc fail");
	free(tmp);
} */

bool	first_last(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (true);
	return (false);
}

ec"h"o

ec
"h"
o \0

void	expand_string(t_data *data, t_mlist *node)
{
	char	*tmp;
	char	*tmp2;
	t_mlist	*env_res;

	if (node->token == STRING_SQ)
	{
		trim_n_free(data, node, '\'');
		return ;
	}
	if (node->token == STRING_DQ)
		trim_n_free(data, node, '\"');
	tmp = variable_to_value(data, ft_split(node->str, '$'));
	if (node->str[ft_strlen(node->str) - 1] == '$')
		tmp2 = ft_strjoin(tmp, "$");
	// tmp = ft_strchr(node->str, '$');
	// while (tmp != NULL)
	// {
	// 	tmp2 = variable_to_value(data, tmp);
	// 	ft_strjoin()
	// 	tmp = ft_strchr(tmp, '$');
	// 	if (tmp + 1 == '\0')
	// 		return ;
	// 	env_res = find_input(data->env, tmp + 1);
	// 	if (env_res != NULL)
	// 	{
	// 		*tmp = '\0';
	// 		tmp = node->str;
	// 		node->str = ft_strjoin(tmp, env_res->str);
	// 		free(tmp);
	// 	}
	// }
}

void	expansion_pack(t_data *data, t_mlist *input)
{
	while (input != NULL)
	{
		expand_string(data, input);
		input = input->nx;
	}
}
