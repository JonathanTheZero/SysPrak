struct shm_data
{
	int x;
	int y;
	int counter;
};

void shm_init();

struct shm_data *shm_call();

void close_shm();

void inc_prog_counter();
