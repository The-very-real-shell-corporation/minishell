/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dir_test.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lotse <lotse@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 11:23:42 by lotse         #+#    #+#                 */
/*   Updated: 2023/11/09 13:45:57 by lotse         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	DIR 			*dir;
	struct dirent	*dirdir;
	
	if (argc != 2)
		return (printf("specify directory\n"), 1);
	dir = opendir(argv[1]);
	if (dir == NULL)
		return (perror("Error"), errno);
	errno = 0;
	while (1)
	{
		dirdir = readdir(dir);
		if (dirdir == NULL)
		{
			if (errno != 0)
				return (perror("Error"), errno);
			else
				break;	
		}
		printf("%s\n", dirdir->d_name);
	}
	if (closedir(dir) != 0)
		return (perror("Error"), errno);
	return (0);
}
