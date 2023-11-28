/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lotse <lotse@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 16:53:10 by lotse         #+#    #+#                 */
/*   Updated: 2023/11/28 19:46:50 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	char	s[100];
	size_t	s_len;
	int		fd[2];
	pid_t	p_id;
	
	if (argc != 2)
		return(printf("Use: ./pipe_test.out [message]"));
	// fd[0] = open(argv[2])
	pipe(fd);
	s_len = strlen(argv[1]);
	p_id = fork();
	if (p_id < 0)
		return (perror("Error"), errno);
	else if (p_id > 0)
	{
		close(fd[1]);
		wait(NULL);
		if (read(fd[0], &s, s_len) < 0)
			return (perror("Error with read()"), close(fd[0]), errno);
		close(fd[0]);
		printf("message: %s\n", s);
	}
	else
	{
		close(fd[0]);
		if (write(fd[1], argv[1], s_len) < 0)
			return (perror("Error with write()"), close(fd[1]), errno);
		close(fd[1]);
	}

	return (0);
}
