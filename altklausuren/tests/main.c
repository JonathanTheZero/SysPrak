#include "shm.h"
#include "pipe.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "io.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ll.h"

extern char *optarg;

int main(int argc, char *argv[])
{
	shm_init();
	struct shm_data *data = shm_call();
	printf("SHM-Data: x: %i, y: %i\n", data->x, data->y);
	close_shm();

	char *str = "Hello World\0";
	int len = strlen(str) + 1;

	int a, b, opt;
	while ((opt = getopt(argc, argv, "a:b:")) != -1)
	{
		switch (opt)
		{
		case 'a':
			a = atoi(optarg);
			break;
		case 'b':
			b = atoi(optarg);
			break;
		default:
			printf("Unknown param!\n");
			break;
		}
	}

	printf("A: %i, B: %i\n", a, b);

	io_test();

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

		waitpid(pid, NULL, 0);
		printf("Child terminated successfully.\n");
	}
	else
	{
		pipe_read(fd, len);
		exit(0);
	}

	ll_t *list = malloc(sizeof(ll_t));
	list->next = NULL;
	list->val = 1;

	addElementEnd(list, 2);
	addElementFront(&list, 0);
	addElementFront(&list, -1);
	addElementEnd(list, 3);

	printElements(list);

	int counter = countElements(list);
	printf("Liste hat %i Elemente.\n", counter);

	freeList(list);

	/*pid = getpid();

	for(int i = 0; i < 7; i++){
		int fpid = fork();
		inc_prog_counter();
		if(fpid > 0) {
			waitpid(fpid, NULL, 0);
		}
	}

	if(getpid() != pid){
		exit(0);
		}

	data = shm_call();
	printf("Counter: %i\n", data->counter);*/

	return 0;
}
