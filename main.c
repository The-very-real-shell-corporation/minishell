/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/03 14:00:30 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	re_lexing(char *envp)
// {
// 	enum token{PIPE, PIPE};
	
// 	enum token thing;

// 	thing = 0;
// 	printf("%d", thing);
// }

void	exit_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

t_mlist	*parse_input(char *line)
{
	t_mlist	*list;
	
	list = chop_string(line);
	if (list != NULL)
		analyze_input(list);
	return (list);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mlist	*list;

	(void)argv;
	(void)envp;
	(void)argc;
	i = 0;
	while (true)
	{
		line = readline("Much wow: ");
		if (line == NULL)
			exit_error("Readline failed");
		add_history(line);
		list = parse_input(line);
		if (list != NULL)
		{
			print_list(list);
			clear_mlist(&list);
		}
		usleep(1000);
	}
	return (0);
}
