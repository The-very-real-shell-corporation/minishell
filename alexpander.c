/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexpander.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 17:27:05 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/14 20:40:40 by vvan-der      ########   odam.nl         */
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

/* void	expand_string(t_data *data, t_mlist *node)
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
} */
static bool	quote_marks(char c)
{
	char	values[] = {'\'', '\"', '\0'};
	int		i;

	i = 0;
	while (values[i] != '\0')
	{
		if (values[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*expand_single(t_data *data, char *str)

char	*expand_dollar(t_data *data, char *str)
{
	char	**split;
	char	*tmp;
	int		x;
	int		i;
	bool	sq;

	i = 0;
	x = 0;
	sq = false;
	split = ft_split(str, '$');
	if (split == NULL)
		exit_error(data, "split failed");
	while (split[x] != NULL)
	{
		
		// tmp = NULL;
		// while (split[x][i] != '\0')
		// {
		// 	if (quote_marks(split[x][i]) == true)
		// 	{
		// 		tmp = ft_strdup2(data, split[x]);
		// 		if (tmp == NULL)
		// 			exit_error(data, "malloc fail");
		// 		tmp[i] = '\0';
		// 		if (split[x][i] == '\'')
		// 		{
		// 			if (sq == false)
		// 				sq = true;
		// 			else
		// 				sq = false;
		// 		}
		// 	}
		// 	i++;
		// }
		// if (tmp != NULL)
		// 	data->env = find_input(data->env, tmp);
		// else
		// 	data->env 
		// i = 0;
		// x++;		
	}
	// int		i;
	// int		j;
	// bool	quote;
	// char	*tmp;

	// i = 0;
	// j = 0;
	// quote = false;
	// tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	// while (str[i] != '\0')
	// {
	// 	if (str[i] == '\'' && ft_strchr(str[i + 1], '\'') != NULL)
	// 		quote = true;
	// 	if (str[i] == '$' && str[i + 1] != '\0' && quote == false)
	// 	{
	// 		i++;
	// 		while (str[i] != '\0' && quote_marks(str[i]) == false && str[i] != '$')
	// 			tmp[j] = str[i];
			
	// 	}
	// 	i++;
	// }
}

char	*remove_char(char *str, char c)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			str++;
		res[i] = str[i];
		i++;
	}
	return (res);
}


void	remove_quotes(t_data *data, t_mlist *node)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	str = node->str;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (quote_marks(str[i]) == true)
		{
			if (ft_strchr(&str[i + 1], str[i]) != NULL)
			{
				tmp = remove_char(str, str[i]);
				if (tmp == NULL)
					exit_error(data, "malloc error");
			}
			break ;
		}
		i++;
	}
	if (tmp != NULL)
	{
		node->str = tmp;
		free(str);
	}
}

void	expansion_pack(t_data *data, char *input)
{
	t_mlist	*split;

	split = ft_special_split(data, input);
	data->input = split;
	if (split != NULL)
		analyze_input(data);
	while (split != NULL)
	{
		expand_dollar(data, split->str);
		remove_quotes(data, split);
		// expand_string(data, input);
		split = split->nx;
	}
}
