/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:51:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/29 22:05:24 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*monitor_thread(void *arg)
{
	t_program	*program;
	int			ret;

	if (!arg)
		return (NULL);
	program = (t_program *)arg;
	ret = 0;
	while (!ret)
	{
		ret = check_program_ready(program);
		if (ret == -1)
			return (NULL); // TODO: stop all threads
	}
	ret = 1;
	while (ret)
	{
		ret = check_program_philo_died(program);
		if (ret == -1)
			return (printf("mutex error\n"), NULL); // TODO: stop all threads
		if (ret == 1)
		{
			printf("END OF SIMULATION UNSUCCESSFULLY...PHILO DIED\n");
			break ;
		}
		ret = check_program_finished(program);
		if (ret == -1)
			return (printf("mutex error\n"), NULL); // TODO: stop all threads
		if (ret == program->n_philos)
		{
			printf("END OF SIMULATION SUCCESSFULLY...\n");
			break ;
		}
		ret = 1;
		usleep(8 * 1000);
	}
	return (NULL);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	long		meals;
	int			ret;
	bool		died;

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
	philo->last_meal = get_time();
	// printf("PHILO %d: F-> %d S-> %d\n", philo->id, philo->first_fork->id, philo->second_fork->id);
	if (philo->id % 2 == 0)
		usleep(10 * 1000);
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
		__u_int	current = get_time();
		died = current - philo->last_meal > program->t_die;
		printf("PHILO %d is eating for the %ldth time since (%u ms) -> DIED: %d...\n", philo->id, meals + 1, current - philo->last_meal, died);
		if (died)
		{
			printf("PHILO %d died .. END OF SIMULATION\n", philo->id);
			// clear_forks(program->forks, program->n_philos);
			// clear_philos(program->philos, program->n_philos);
			// free(program);
			// exit(EXIT_FAILURE);
			if (set_program_philo_died(program) == -1)
				return (printf("error dying\n"), NULL); // TODO: stop all threads
			return (NULL);
		}
		philo->last_meal = current;
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
	if (set_program_finished(program) == -1)
		return (NULL); // TODO: stop all threads
	return (NULL);
}

// void	start_threads(t_program *program, t_philo **philos, t_fork **forks)
void	start_threads(t_program *program)
{
	__u_int	i;
	t_philo	**philos;
	t_fork	**forks;
	int		ret;

	philos = program->philos;
	forks = program->forks;
	/* create threads */
	i = 0;
	while (i < program->n_philos)
	{
		ret = pthread_create(&philos[i]->thread, NULL, philo_thread, (void *)philos[i]);
		if (ret != 0)
			return (printf("error creating thread\n"), (void)0);
		i++;
	}
	ret = pthread_create(&program->monitor, NULL, monitor_thread, (void *)program);
	if (ret != 0)
		return (printf("error creating thread\n"), (void)0);
	if (set_program_ready(program) == -1)
		return ;

	/* join thread */
	// i = 0;
	// while (i < program->n_philos)
	// {
	// 	ret = pthread_join(philos[i]->thread, NULL);
	// 	if (ret != 0)
	// 		return (printf("error joining thread\n"), (void)0);
	// 	i++;
	// }
	ret = pthread_join(program->monitor, NULL);
	if (ret != 0)
		return (printf("error joining thread\n"), (void)0);
}
