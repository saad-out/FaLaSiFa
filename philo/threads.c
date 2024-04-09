/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:51:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/09 14:56:43 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	// philo->last_meal = get_time();
	if (set_philo_last_meal(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		return (NULL);
	}
	/* lunch impair philos first */
	if (philo->id % 2 == 0)
		usleep(10 * 1000);
	meals = 0;
	while (program->max_meals == -1 || meals < program->max_meals)
	{
		if (!get_forks(philo, program))
			break ;
		if (!eat(philo, program))
			break ;
		if (!put_forks(philo, program))
			break ;
		if (++meals == program->max_meals)
			continue ;
		if (!sleep_p(philo, program))
			break ;
		if (!think(philo, program))
			break ;
	}
	if (set_program_finished(program) == -1 || set_philo_finished(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		pthread_exit(NULL);
	}
	return (NULL);
}

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

	/* join philo threads */
	i = 0;
	while (i < program->n_philos)
	{
		ret = pthread_join(philos[i]->thread, NULL);
		if (ret != 0)
			return (printf("error creating thread\n"), (void)0);
		i++;
	}
	/* join monitor thread */
	ret = pthread_join(program->monitor, NULL);
	if (ret != 0)
		return (printf("error joining thread\n"), (void)0);
}
