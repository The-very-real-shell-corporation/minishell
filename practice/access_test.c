/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akasiota <akasiota@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/27 18:54:03 by akasiota      #+#    #+#                 */
/*   Updated: 2023/10/27 21:25:22 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv, char** envp)
{
	if (argc < 2)
	{
		printf("Usage: ./access.out <arg>\n");
		return (-1);
	}
	if (access(argv[1], X_OK) == 0) /* Second argument can be: F_OK || X_OK or F_OK && X_OK (not really important in our case) */
	{
		if (execve(argv[1], argv, envp) == -1)
		{
			printf("execve(%s) failure\n", argv[1]);
			return (-3);
		}
	}
	else
	{
		printf("access(%s) failure\n", argv[1]);
		return (-2);
	}
	return (0);
}
