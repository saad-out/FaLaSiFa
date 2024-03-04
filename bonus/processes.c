/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/04 15:12:58 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philo_process(t_program *program, sem_t *sem, int id)
{
	__u_int	meals;
	__u_int	i;
	int		ret;

	if (id % 2 == 0)
		usleep(10 * 1000);
	meals = 0;
	while (program->max_meals == -1 || meals < program->max_meals)
	{
		/* get forks */
		ret = sem_wait(sem);
		if (ret == -1)
			return (printf("error waiting sem\n"), exit(EXIT_FAILURE));
		printf("philo %d has taken first fork\n", id);
		ret = sem_wait(sem);
		if (ret == -1)
			return (printf("error waiting sem\n"), exit(EXIT_FAILURE));
		printf("philo %d has taken second fork\n", id);

		/* eat */
		printf("philo %d is now eating for the %uth time...\n", id, meals + 1);
		usleep(program->t_eat * 1000);

		/* release forks */
		ret = sem_post(sem);
		if (ret == -1)
			return (printf("error posting sem\n"), exit(EXIT_FAILURE));
		printf("pihlo %d put down first  fork\n", id);
		ret = sem_post(sem);
		if (ret == -1)
			return (printf("error posting sem\n"), exit(EXIT_FAILURE));
		printf("pihlo %d put down second fork\n", id);

		/* sleep */
		printf("philo %d is sleeping...\n", id);
		usleep(program->t_sleep * 1000);

		/* think */
		printf("philo is now thinking...\n");
	
		meals++;
	}
	printf("philo %d finished...\n", id);
}

void	start_processes(t_program *program, sem_t *sem)
{
	pid_t	pid;

	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = fork();
		if (pid == -1)
			return (printf("fork error\n"), (void)0);
		else if (pid == 0)
		{
			philo_process(program, sem, i + 1);
			if (sem_close(sem) == -1)
				return (printf("error closing semaphor\n"),free(program), exit(EXIT_FAILURE));
			free(program);
			exit(EXIT_SUCCESS);
		}
	}
	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = wait(NULL);
		printf("child terminated\n");
	}
}
