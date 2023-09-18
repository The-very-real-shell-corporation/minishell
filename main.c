/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/18 17:43:37 by vvan-der      ########   odam.nl         */
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
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	parse_input(char **in, char *input)
{
	if (in != NULL)
		free_2D(in);
	in = chop_string(input);
	analyze_input(in);
}

void	leaks(void)
{
	system("leaks -q minishell"); 
}

int	main(int argc, char **argv, char **envp)
{
	char	*tmp;
	char	**input;

	atexit(leaks);
	(void)argv;
	(void)envp;
	(void)argc;
	input = NULL;
	// printf("%s\n", argv[0]);
	// re_lexing(*envp);
	while (true)
	{
		tmp = readline("Much wow: ");
		add_history(tmp);
		parse_input(input, tmp);
		rl_redisplay();
		
		// if (ft_strncmp(tmp, "pwd", 3) == 0)
		// 	pwd_builtin();
		// else if (ft_strncmp(tmp, "echo -n", 7) == 0)
		// 	echo_builtin(tmp + 8, "-n");
		// else if (ft_strncmp(tmp, "echo", 4) == 0)
		// 	echo_builtin(tmp + 5, NULL);
		// else if (ft_strncmp(tmp, "cd", 2) == 0)
		// 	cd_builtin(tmp + 3);
		// else if (ft_strncmp(tmp, "env", 3) == 0)
		// 	env_builtin(envp);
		usleep(1000);
	}
	return (0);
}
