/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lotse <lotse@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 16:53:10 by lotse         #+#    #+#                 */
/*   Updated: 2023/11/10 17:07:04 by lotse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int		fd[2];
	pid_t	p_id;
	
	if (argc != 3)
		return(printf("Use: ./pipe_test.out [message] [filename]"));
	fd[0] = open(argv[2])
	p_id = fork()
	if (p_id < 0)
		return (perror("Error"), errno);
	else if (p_id > 0)
	{
		
	}
	else
	{
		
	}
}