/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dup_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lotse <lotse@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 13:03:30 by lotse         #+#    #+#                 */
/*   Updated: 2023/11/10 16:45:05 by lotse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int	fd_1;
	int	fd_2;
	int	fd_check;
	
	if (argc != 3)
		return (printf("Use: ./dup_test.out [message] [filename]\n"), 1);
	
	fd_1 = 1;
	fd_2 = open(argv[2], O_WRONLY | O_CREAT, 0644);
	if (fd_2 < 0)
		return (perror("Error"), errno);
	fd_check = dup2(fd_2, fd_1); /* First argument is where it "writes", Second argument is where it "reads" from */
	if (fd_check < 0)
		return (perror("Error"), errno);
	// printf("fd_check: %d\n", fd_check);
	write(fd_1, argv[1], strlen(argv[1]));
	close(fd_2);
	return (0);
}