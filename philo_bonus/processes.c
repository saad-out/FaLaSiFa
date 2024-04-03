/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/03 15:12:32 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	start_threads(t_philo *philo)
{
	t_program *program;
	pthread_t	monitor_t;
	pthread_t	philo_t;
	int			ret;
	void		*ret_value;

	/* init */
	program = philo->program;

	/* create threads */
	ret = pthread_create(&philo_t, NULL, philo_thread, (void *)philo);
	if (ret != 0)
		perror("pthread_create"), exit(EXIT_FAILURE);
	ret = pthread_create(&monitor_t, NULL, monitor_thread, (void *)philo);
	if (ret != 0)
		perror("pthread_create"), exit(EXIT_FAILURE);

	/* join monitor */
	ret = pthread_join(monitor_t, &ret_value);
	if (ret != 0)
		perror("pthread_join"), exit(EXIT_FAILURE);

	/* join philo */
	ret = pthread_join(philo_t, NULL);
	if (ret != 0)
		perror("pthread_join"), exit(EXIT_FAILURE);

	/* cleanup */
	clear_philos(philo->program->philos, philo->program->n_philos, false);
	if (sem_close(program->sem) == -1)
		perror("sem close 1 prog");
	free(program);

	/* exit status */
	ret = *(int *)ret_value;
	free(ret_value);
	exit(ret);
}

void	start_processes(t_program *program)
{
	pid_t	pid;
	sem_t	*sem;
	t_philo	**philos;
	int		status;

	sem = program->sem;
	philos = program->philos;
	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = fork();
		if (pid == -1)
			return (printf("fork error\n"), (void)0);
		else if (pid == 0)
		{
			start_threads(philos[i]);
			printf("start_threads should not return\n");
			exit(EXIT_FAILURE);
		}
		else
			philos[i]->pid = pid;
	}
	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			perror("waitpid"), exit(EXIT_FAILURE); // TODO: clear resources
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == EXIT_FAILURE)
				printf("child %d died\n", pid);
			else
				printf("child %d done eating\n", pid);
		}
		else if (WIFSIGNALED(status))
			printf("child %d exited due to signal %d\n", pid, WTERMSIG(status));
		else
			printf("ma3rfanch\n");
	}
}
