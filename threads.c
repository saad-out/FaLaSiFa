/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:51:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 23:42:33 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	long		meals;
	int			ret;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	program = philo->program;
	ret = 0;
	while (!ret)
	{
		ret = check_program_ready(program);
		if (ret == -1)
			return (NULL); // TODO: stop all threads
	}
	// printf("PHILO %d: F-> %d S-> %d\n", philo->id, philo->first_fork->id, philo->second_fork->id);
	meals = 0;
	while (program->max_meals == -1 || meals < program->max_meals)
	{
		// get forks
		ret = pthread_mutex_lock(&philo->first_fork->mutex);
		if (ret != 0)
			return (NULL); // TODO: stop all threads
		printf("PHILO %d has first fork %d\n", philo->id, philo->first_fork->id);
		ret = pthread_mutex_lock(&philo->second_fork->mutex);
		if (ret != 0)
			return (NULL); // TODO: stop all threads
		printf("PHILO %d has second fork %d\n", philo->id, philo->second_fork->id);
		
		// eat
		printf("PHILO %d is eating for the %ldth time...\n", philo->id, meals + 1);
		usleep(program->t_eat * 1000);

		// put forks
		ret = pthread_mutex_unlock(&philo->first_fork->mutex);
		if (ret != 0)
			return (NULL); // TODO: stop all threads
		printf("PHILO %d PUT first fork %d\n", philo->id, philo->first_fork->id);
		ret = pthread_mutex_unlock(&philo->second_fork->mutex);
		if (ret != 0)
			return (NULL); // TODO: stop all threads
		printf("PHILO %d PUT second fork %d\n", philo->id, philo->second_fork->id);

		// sleep
		printf("PHILO %d is sleeping...\n", philo->id);
		usleep(program->t_sleep * 1000);

		// think
		printf("PHILO %d is thinking...\n", philo->id);

		meals++;
	}
	printf("PHILO %d finished...\n", philo->id);
	return (NULL);
}

void	start_threads(t_program *program, t_philo **philos, t_fork **forks)
{
	__u_int	i;
	int		ret;

	/* create threads */
	i = 0;
	while (i < program->n_philos)
	{
		ret = pthread_create(&philos[i]->thread, NULL, philo_thread, (void *)philos[i]);
		if (ret != 0)
			return (printf("error creating thread\n"), (void)0);
		i++;
	}
	if (set_program_ready(program) == -1)
		return ;

	/* join thread */
	i = 0;
	while (i < program->n_philos)
	{
		ret = pthread_join(philos[i]->thread, NULL);
		if (ret != 0)
			return (printf("error joining thread\n"), (void)0);
		i++;
	}
}
