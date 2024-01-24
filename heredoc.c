/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/24 12:26:57 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	doodle_in_doc(t_data *data, char *delim)
{
	bool	expansion;
	char	*line;

	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	while (INFINITY)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, delim, ft_strlen(delim)) == 0)
			break ;
		if (expansion == true)
			expand_dollar(data, &line);
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
	free(line);
}

/*	To do: implement signals so interrupting heredoc doesn't close minishell and make sure
ctrl + D works (EOF)	*/

void	whatsup_doc(t_data *data, t_mlist *input)
{
	doodle_in_doc(data, input->str);
	// return (doodle_in_doc(data, NULL, NULL, input->nx->str));
}
