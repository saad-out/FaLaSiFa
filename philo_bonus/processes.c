/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 23:50:25 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	start_threads(t_philo *philo)
{
	pthread_t	monitor_t;
	pthread_t	philo_t;
	int			ret;
	void		*ret_value;

	ret = pthread_create(&philo_t, NULL, philo_thread, (void *)philo);
	if (ret != 0)
		perror("pthread_create"), exit(EXIT_FAILURE);
	ret = pthread_create(&monitor_t, NULL, monitor_thread, (void *)philo);
	if (ret != 0)
		perror("pthread_create"), exit(EXIT_FAILURE);

	printf("philo %d success creating of threads\n", philo->id);

	ret = pthread_join(monitor_t, &ret_value);
	if (ret != 0)
		perror("pthread_join"), exit(EXIT_FAILURE);
	printf("monitor %d said philo %d exited with %d\n", philo->id, philo->id, *(int *)ret_value);
	free(ret_value);
	ret = pthread_detach(philo_t);
	if (ret != 0)
		perror("pthread_detach"), exit(EXIT_FAILURE);
	if (sem_close(philo->program->sem) == -1)
		perror("sem close 1 prog");
	clear_philos(philo->program->philos, philo->program->n_philos, false);
	free(philo->program);
	exit(*((int *)ret_value));
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
			// philo_thread(philos[i]);
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
