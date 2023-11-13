#include "minishell.h"

int	main()
{
	int array[6] = {5, 5, 4, 3, 2, 1};
	int	id;
	int result;
	int result2;
	int start;
	int end;
	int fd[2];

	end = sizeof(array) / sizeof(int);
	start = 0;
	result = 0;
	result2 = 0;
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		start = end / 2;
		for (int i = start; i < end; i++)
			result2 += array[i];
		puts("Second?");
		write(fd[1], &result2, sizeof(result2));
		printf("Child says: WEHH and number: %d\n", result2);
		close(fd[1]);
	}
	else
	{
		int x = 0;
		close(fd[1]);
		end = end / 2;
		for (int i = start; i < end; i++)
			result += array[i];
		printf("Adult says: WEHH and number: %d\n", result);
		puts("First?");
		read(fd[0], &x, sizeof(x));
		printf("Final result!!!!111(one)!: %d\n", result + x);
		close(fd[0]);
		wait(NULL);
	}
	puts("HI");
}