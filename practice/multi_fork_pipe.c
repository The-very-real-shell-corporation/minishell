#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

// #define PROCESS_NUM 3

int	main(int argc, char *argv[])
{
	int i;

	if (argc != 3)
	{
		printf("[./a.out] [PROCESS_NUM] [NUMBER_TO_INCREMENT]\n");
		return (10);
	}
	int	process_num = atoi(argv[1]);
	int num_to_incr = atoi(argv[2]);
	int	pipes[process_num + 1][2];
	int pids[process_num];
	for (i = 0; i < process_num + 1; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Couldn't create pipe\n");
			return (1);
		}
	}

	for (i = 0; i < process_num; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Couldn't create fork\n");
			return (2);
		}
		if (pids[i] == 0)
		{
			int	j;
			for (j = 0; j < process_num + 1; j++)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
			}
			int	x;
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{	
				printf("Error reading pipe\n");
				return (3);

			}
			printf("(%d) Got %d\n", i, x);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				printf("Error writing in pipe\n");
				return (4);
			}
			printf("(%d) Sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return (0);
		}
	}

	int	j;
	for (j = 0; j < process_num + 1; j++)
	{
		if (j != process_num)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
	}
	int	y = num_to_incr;
	printf("Main process sent %d\n", y);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
	{
		printf("Error writing in pipe\n");
		return (4);
	}
	if (read(pipes[process_num][0], &y, sizeof(int)) == -1)
	{
		printf("Error reading pipe\n");
		return (3);
	}
	close(pipes[0][1]);
	close(pipes[process_num][0]);
	printf("The final result is %d\n", y);
	for (i = 0; i < process_num; i++)
	{
		waitpid(pids[i], NULL, 0);
	}
	return (0);
}