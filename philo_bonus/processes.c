/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/05 23:49:07 by soutchak         ###   ########.fr       */
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
	// printf("%s monitor done%s\n", philo->color, RESET);

	/* join philo */
	ret = pthread_join(philo_t, NULL);
	if (ret != 0)
		perror("pthread_join"), exit(EXIT_FAILURE);
	// ret = pthread_detach(philo_t);
	// if (ret != 0)
	// 	perror("pthread_join"), exit(EXIT_FAILURE);
	// printf("%s philo done%s\n", philo->color, RESET);

	/* cleanup */
	// printf("===> philo %d done\n", philo->id);
	int id = philo->id;
	char *color = philo->color;
	clear_philos(philo->program->philos, philo->program->n_philos, false);
	if (sem_close(program->var_lock) == -1)
		perror("sem close 1 prog");
	if (sem_close(program->print_lock) == -1)
		perror("sem close 1 prog");
	if (sem_close(program->forks) == -1)
		perror("sem close 1 prog");
	free(program);

	/* exit status */
	ret = *(int *)ret_value;
	free(ret_value);
	// printf("%s************* PHILO %d GOING TO EXIT WITH %d%s\n",color, id, ret, RESET);
	exit(ret);
}

void	start_processes(t_program *program)
{
	pid_t	pid;
	// sem_t	*sem;
	t_philo	**philos;
	int		status;

	// sem = program->sem;
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
			// printf("===> CHILD %d exited with %d\n", pid, WEXITSTATUS(status));
			if (WEXITSTATUS(status) == EXIT_FAILURE)
			{
				// printf("lets kill\n");
				// sem_wait(program->print_lock);
				kill_all_except(philos, program->n_philos, pid);
				break ;
			}
		}
		else if (WIFSIGNALED(status))
		{
			// printf("child %d exited due to signal %d\n", pid, WTERMSIG(status));
			kill_all_except(philos, program->n_philos, pid);
			break ;
		}
		else
		{
			// printf("ma3rfanch\n");
			kill_all_except(philos, program->n_philos, pid);
			break ;
		}

		// int	val;
		// sem_getvalue(program->sem, &val);
		// printf("=======> SEM VALUE AFTER CHILD EXITED %d\n", val);
	}
}
