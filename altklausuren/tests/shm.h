struct shm_data {
	int x;
	int y;
};

void shm_init();

struct shm_data *shm_call();

void close_shm();
