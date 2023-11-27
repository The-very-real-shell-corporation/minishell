/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/27 20:23:53 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	struct termios	t_erm;
	// t_data	*data;
	(void)info;
	(void)context;
	// data = (t_data *)context;
	if (info->si_pid == 0 && signal == SIGINT)
		write(1, "\n", 1);
	else if (signal == SIGINT)
	{
		// printf("\n");
		// rl_replace_line("\n", STDOUT_FILENO);
		// rl_replace_line("\n", STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (info->si_pid == 0 && signal == SIGQUIT)
		write(1, "\nJOVIIIII", 9);
	else if (signal == SIGQUIT)
	{
		// write(1, "\nsouvlaki", 9);
		rl_on_new_line();
		rl_redisplay();
		tcsetattr(STDOUT_FILENO, )
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	// pid_t	id;
	struct sigaction	sa;
	// char	*test;

	(void)argv;
	if (argc != 1)
		return (printf("Please insert input after starting minishell"), 1);
	initialize_data(&data, envp);
	init_sigaction(&sa);
	data.cwd = getcwd(NULL, 0);
	sigaction(SIGINT, &sa, NULL);	// ctrl c
	sigaction(SIGQUIT, &sa, NULL);	// ctrl '\'
	// signal(SIGQUIT, SIG_IGN);
	while (INFINITY)
	{
		line = readline("Much wow: ");
		if (line == NULL)
		{
			clean_up(&data);
			exit(0);
		}
			// exit_error(&data, "Readline failed");
		parse_input(&data, line);
		if (ft_strncmp(line, "cd", 2) == 0)
			cd_builtin(&data, data.argv[1]);
		if (ft_strncmp(line, "env", 3) == 0)
			env_builtin(&data);
		if (ft_strncmp(line, "export", 6) == 0)
		{
			export_builtin(&data, &line[7]);
		}
		if (ft_strncmp(line, "unset", 5) == 0)
			unset_builtin(&data, &line[6]);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit_builtin(&data, NULL);
		// id = fork();
		// if (id == 0)
		// {
		// 	search_the_path(&data, data.path);
		// 	// signal(SIGQUIT, simple_handler);
		// 	// signal(SIGINT, simple_handler);
		// }
		// // else
		// // {
		// 	// signal(SIGQUIT, simple_handler);
		// 	// signal(SIGINT, simple_handler);
		// // }
		// wait(&data.exit_status);
		printf("exit status: %d\n", data.exit_status);
		add_history(line);
		usleep(1000);
	}
	return (0);
}
