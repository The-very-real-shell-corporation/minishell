/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 18:13:48 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*doodle_in_doc(t_data *data, t_mlist *doc, t_mlist *tmp, char *delim)
{
	bool	expansion;
	char	*line;

	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	while (INFINITY)
	{
		line = readline("> ");
		if (line == NULL || \
		ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			break ;
		if (expansion == true)
			expand_dollar(data, &line);
		node_addback(&doc, \
		new_node(data, ft_strdup2(data, line), NULL, INITIALIZED));
		free(line);
	}
	if (doc != NULL)
		tmp = new_node(data, NULL, list_to_array(data, doc), DOC_INPUT);
	clear_mlist(&doc);
	return (tmp);
}

/*	To do: implement signals so interrupting heredoc doesn't close minishell and make sure
ctrl + D works (EOF)	*/

t_mlist	*whatsup_doc(t_data *data, t_mlist *input)
{
	if (input->nx == NULL || input->nx->token != DOC_DELIM)
	{
		write(STDERR_FILENO, "Could not find heredoc delimiter\n", 34);
		return (NULL);
	}
	return (doodle_in_doc(data, NULL, NULL, input->nx->str));
}
