#include "pipe.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void pipe_write(int *fd, const char *str, int len)
{
	close(fd[0]);

	int len_written = write(fd[1], str, len);
	printf("Sent %i bytes\n", len_written);
	if (len_written < 0 || len_written != len)
	{
		perror("write");
		exit(-1);
	}

	close(fd[1]);
}

void pipe_read(int *fd, int len)
{
	close(fd[1]);

	char buf[len];

	int len_read = read(fd[0], buf, len);
	if (len_read < 0 || len_read != len)
	{
		perror("read");
		exit(-1);
	}

	printf("Received: %s\n", buf);

	close(fd[0]);
}
