#include "io.h"
#include <stdio.h>
#include <string.h>

void io_test()
{
	FILE *file = fopen("./test.conf", "r+");
	if (file == NULL)
	{
		printf("File does not exist, creating it...\n");
		file = fopen("./test.conf", "w");
	}

	char *test = "Hello World\0";

	int written = fwrite(test, sizeof(char), strlen(test) + 1, file);
	printf("Wrote %i bytes.\n", written);

	fclose(file);
}
