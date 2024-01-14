/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/14 17:04:44 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_command_token(t_mlist *node, char *str)
{
	if (ft_strncmp("cd", str, 3) == 0)
		node->token = B_CD;
	else if (ft_strncmp("echo", str, 5) == 0)
		node->token = B_ECHO;
	else if (ft_strncmp("env", str, 4) == 0)
		node->token = B_ENV;
	else if (ft_strncmp("exit", str, 5) == 0)
		node->token = B_EXIT;
	else if (ft_strncmp("export", str, 7) == 0)
		node->token = B_EXPORT;
	else if (ft_strncmp("pwd", str, 4) == 0)
		node->token = B_PWD;
	else if (ft_strncmp("unset", str, 6) == 0)
		node->token = B_UNSET;
	else
		node->token = COMMAND;
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
	else if (ft_strncmp(str, "-n", 3) == 0)
		token = ECHO_FLAG;
	else
		token = WORD;
	return (token);
}

void	tokenize_list(t_mlist *in)
{
	while (in != NULL)
	{
		in->token = assign_token(in->str);
		if (in->pv != NULL && in->pv->token == HEREDOC && in->token == WORD)
			in->token = HEREDOC_DELIM;
		if ((in->pv == NULL && in->token != HEREDOC) || \
			(in->pv != NULL && in->pv->token == PIPE))
			assign_command_token(in, in->str);
		in = in->nx;
	}
}

void	analyze_input(t_data *data)
{
	if (data->input == NULL)
		printf("%s\n", "error: invalid input");
	else
		tokenize_list(data->input);
	if (go_to_token(&data->input, HEREDOC) == true) // calculate amount of heredocs and add their ->nx->str's to **delims
	{
		whatsup_doc(data, node_first(data->input));
	}
	data->input = node_first(data->input);
}
