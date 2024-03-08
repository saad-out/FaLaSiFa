#include "../main.h"

int main()
{
	if (sem_unlink("forks") == -1)
		return (printf("error unlinking semaphor\n"), exit(EXIT_FAILURE), 9);
	return (0);
}