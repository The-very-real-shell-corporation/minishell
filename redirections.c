/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/20 15:04:31 by vincent       #+#    #+#                 */
/*   Updated: 2024/01/22 21:05:07 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>

// int main() {
//     // File path
//     const char *filePath = "your_file.txt";

//     // Open the file in append mode with maximum permissions
//     int fileDescriptor = open(filePath, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);

//     // Check if the file was opened successfully
//     if (fileDescriptor == -1) {
//         perror("Error opening the file");
//         return 1; // Exit the program with an error code
//     }

//     // File operations go here...

//     // Close the file when done
//     close(fileDescriptor);

//     return 0; // Exit the program successfully
// }


int	append_output(t_data *data, char *pathname)
{
	int	fd;

	printf("pathname: %s\n", pathname);
	fd = open(pathname, O_WRONLY | 00777 | O_CREAT, O_APPEND);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	// dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	redirect_output(t_data *data, char *pathname)
{
	int	fd;

	printf("pathname: %s\n", pathname);
	fd = open(pathname, O_RDWR);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	// dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	redirect_input(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_CREAT | O_RDWR);
	if (fd == -1)
		exit_error(data, "failed to open or create file");
	// dup2(fd, STDIN_FILENO);
	return (fd);
}

void	setup_redirection(t_data *data, t_mlist *pipeline)
{
	if (pipeline->pv->token == APPEND)
	{
		data->pipe_fds[0][1] = append_output(data, pipeline->args[0]);
	}
	if (pipeline->pv->token == RE_OUTPUT)
		data->pipe_fds[0][1] = redirect_output(data, pipeline->args[0]);
	if (pipeline->pv->token == RE_INPUT)
		data->pipe_fds[0][0] = redirect_input(data, pipeline->args[0]);
}
