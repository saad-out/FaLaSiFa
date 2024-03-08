#include "main.h"

int main()
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		printf("I am the child process\n");
		sleep(2);
		printf("Child process is exiting\n");
		return (-1);
	}
	else
	{
		printf("I am the parent process\n");
	}	
	pid = waitpid(pid, &status, 0);
	if (pid == -1)
	{
		printf("Error waiting for child process\n");
		return (1);
	}
	if (WIFEXITED(status))
	{
		printf("Child process exited with status %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("Child process was terminated by signal %d\n", WTERMSIG(status));
	}
}