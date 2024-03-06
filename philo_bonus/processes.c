/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/06 18:49:51 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philo_process(t_philo *philo)
{
	__u_int	meals;
	__u_int	i;
	int		ret;
	t_program *program;

	printf("child %d started\n", philo->id);
	program = philo->program;
	if (philo->id % 2 == 0)
		usleep(10 * 1000);
	meals = 0;
	while (program->max_meals == -1 || meals < program->max_meals)
	{
		/* get forks */
		ret = sem_wait(philo->sem);
		if (ret == -1)
			return (printf("error waiting sem\n"), exit(EXIT_FAILURE));
		printf("%d has taken first fork\n", philo->id);
		ret = sem_wait(philo->sem);
		if (ret == -1)
			return (printf("error waiting sem\n"), exit(EXIT_FAILURE));
		printf("%d has taken second fork\n", philo->id);

		/* eat */
		printf("%d is eating\n", philo->id);
		philo->last_meal = get_time();
		usleep(program->t_eat * 1000);

		/* release forks */
		ret = sem_post(philo->sem);
		if (ret == -1)
			return (printf("error posting sem\n"), exit(EXIT_FAILURE));
		ret = sem_post(philo->sem);
		if (ret == -1)
			return (printf("error posting sem\n"), exit(EXIT_FAILURE));

		/* sleep */
		printf("%d is sleeping\n", philo->id);
		usleep(program->t_sleep * 1000);

		/* think */
		printf("%d is thinking\n", philo->id);
	
		meals++;
	}
	// printf("philo %d finished...\n", philo->id);
}

void	start_processes(t_program *program)
{
	pid_t	pid;
	sem_t	*sem;
	t_philo	**philos;

	sem = program->sem;
	philos = program->philos;
	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = fork();
		if (pid == -1)
			return (printf("fork error\n"), (void)0);
		else if (pid == 0)
		{
			philo_process(philos[i]);
			if (sem_close(sem) == -1)
				return (printf("error closing semaphor\n"), free(program), exit(EXIT_FAILURE));
			free(program);
			exit(EXIT_SUCCESS);
		}
		else
			philos[i]->pid = pid;
	}
	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = wait(NULL);
		printf("child terminated\n");
	}
}
