/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 14:46:17 by vvan-der      ########   odam.nl         */
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

/* void	leaks(void)
{
	system("leaks -q minishell"); 
} */

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_mlist	*list;

	// atexit(leaks);
	(void)argv;
	(void)envp;
	(void)argc;
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
		// rl_redisplay();
		
		// if (ft_strncmp(line, "pwd", 3) == 0)
		// 	pwd_builtin();
		// else if (ft_strncmp(line, "echo -n", 7) == 0)
		// 	echo_builtin(line + 8, "-n");
		// else if (ft_strncmp(line, "echo", 4) == 0)
		// 	echo_builtin(line + 5, NULL);
		// else if (ft_strncmp(line, "cd", 2) == 0)
		// 	cd_builtin(line + 3);
		// else if (ft_strncmp(line, "env", 3) == 0)
		// 	env_builtin(envp);
		usleep(1000);
	}
	return (0);
}
