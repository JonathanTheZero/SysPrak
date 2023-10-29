#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "logging.h"

int main()
{
	srand(time(NULL));
	char *name;
	printf("Enter your name:");
	scanf("%s", name);
	int num = rand() % 100 + 1;
	printf("Enter your guess (1 - 100):\n");
	int guess, guesses = 1;
	scanf("%d", &guess);
	while (guess != num)
	{
		printf("Sadly that's not it! Hint: The answer is %s.\n", guess > num ? "smaller" : "bigger");
		guesses++;
		printf("Enter your guess:\n");
		scanf("%d", &guess);
	}
	printf("Congratulations! The answer was %i and you got it in %i guesses!\n", num, guesses);

	writeToLog(guesses, name);
	addTry(guesses, name);
	return 0;
}