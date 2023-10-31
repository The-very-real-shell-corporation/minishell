/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/31 17:38:46 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_command_token(t_mlist **node, char *str)
{
	if (ft_strncmp("echo", str, 4) == 0 || ft_strncmp("cd", str, 2) == 0|| \
	ft_strncmp("pwd", str, 3) == 0 || ft_strncmp("export", str, 6) == 0 || \
	ft_strncmp("unset", str, 5) == 0 || ft_strncmp("env", str, 3) == 0 || \
	ft_strncmp("exit", str, 4) == 0)
	{
		(*node)->token = BUILT_IN;
	}
	else
	{
		(*node)->token = COMMAND;
	}
}

int	assign_token(char *str)
{
	int	token;

	if (ft_strncmp(str, ">>", 3) == 0)
		token = APPEND;
	else if (ft_strncmp(str, "<<", 3) == 0)
		token = HEREDOC;
	else if (ft_strncmp(str, ">", 2) == 0)
		token = RE_OUTPUT;
	else if (ft_strncmp(str, "<", 2) == 0)
		token = RE_INPUT;
	else if (ft_strncmp(str, "|", 2) == 0)
		token = PIPE;
	else if (ft_strncmp(str, "$", 2) == 0)
		token = DOLLAR_SIGN;
	else if (str[0] == '\'')
		token = STRING_SQ;
	else if (str[0] == '\"')
		token = STRING_DQ;
	else if (ft_strncmp(str, "-n", 3) == 0)
		token = ECHO_FLAG;
	else
		token = WORD;
	return (token);
}

void	tokenize_list(t_mlist *list)
{
	t_mlist	*tmp;

	tmp = list;
	if (list != NULL)
	{
		assign_command_token(&list, list->str);
		list = list->nx;
	}
	while (list != NULL)
	{
		list->token = assign_token(list->str);
		if (list->pv->token == PIPE)
			assign_command_token(&list, list->str);
		list = list->nx;
	}
	list = tmp;
}

void	analyze_input(t_data *data)
{
	if (data->input == NULL)
		printf("%s\n", "error: invalid input");
	tokenize_list(data->input);
}
