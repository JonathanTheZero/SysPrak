#include "shm.h"
#include "pipe.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	shm_init();
	struct shm_data *data = shm_call();
	printf("SHM-Data: x: %i, y: %i\n", data->x, data->y);
	close_shm();

	char *str = "Hello World\0";
	int len = strlen(str) + 1;

	int fd[2];
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return -1;
	}

	int pid;
	if ((pid = fork()) < 0)
	{
		perror("fork");
		return -1;
	}
	else if (pid == 0)
	{
		pipe_write(fd, str, len);
	}
	else
	{
		pipe_read(fd, len);
	}

	return 0;
}
