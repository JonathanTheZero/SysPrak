#include "shm.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>

int shmid;

void shm_init()
{
	shmid = shmget(IPC_PRIVATE, sizeof(struct shm_data), IPC_CREAT | 0666);

	if (shmid < 0)
	{
		perror("shmget");
		exit(-1);
	}

	struct shm_data *data = shmat(shmid, NULL, 0);
	data->x = 10;
	data->y = 20;
	data->counter = 0;
	printf("SHM-Data: x: %i, y: %i\n", data->x, data->y);
}

struct shm_data *shm_call()
{
	struct shm_data *data = shmat(shmid, NULL, 0);
	return data;
}

void close_shm()
{
	int res = shmctl(shmid, IPC_RMID, NULL);
	printf("shmctl: %i\n", res);
}

void inc_prog_counter()
{
	struct shm_data *data = shmat(shmid, NULL, 0);
	data->counter++;
}
