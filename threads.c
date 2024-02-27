/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:51:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 23:19:33 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
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
			return (NULL);
	}
	// printf("PHILO %d: F-> %d S-> %d\n", philo->id, philo->first_fork->id, philo->second_fork->id);
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
