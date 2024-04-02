/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:19:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 23:49:55 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void*	monitor_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	bool		died;
	__u_int		time;
	int			*ret_value;

	philo = (t_philo *)arg;
	program = philo->program;
	printf("===========> monitor started %d\n", philo->id);
	died = 0;
	while (!died)
	{
		if (sem_wait(philo->sem) == -1)
		{
			perror("sem wait monitor");
			break ;
		}
		if (philo->finished)
			break ;
		time = get_time();
		if (time - philo->last_meal >= program->t_die)
		{
			philo->died = 1;
			died = 1;
			break ;
		}
		if (sem_post(philo->sem) == -1)
		{
			perror("sem post monitor");
			break ;
		}
		usleep(5 * 1000);
	}
	/* cleanup */
	int id = philo->id;
	// if (sem_close(program->sem) == -1)
	// 	perror("sem close 1 prog");
	// clear_philos(program->philos, program->n_philos, false);
	// free(program);
	printf("===========>(child %d) monitor finished %d (died=%d)\n", getpid(), philo->id, died);
	ret_value = malloc(sizeof(int));
	if (died)
		*ret_value = 1;
	*ret_value = 0;
	return ((void *)ret_value);
	// if (died)
	// 	return ((void *)EXIT_FAILURE);
	// return ((void *)EXIT_SUCCESS);
}

void*	philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	long		meals;
	int			died;

	philo = (t_philo *)arg;
	program = philo->program;
	printf("=> philo %d\n", philo->id);
	meals = 0;
	if (set_philo_last_meal(philo) == -1)
		return (NULL);
	while (program->max_meals == -1 || meals < program->max_meals)
	{
		get_forks(philo, program);
		eat(philo, program);
		put_forks(philo, program);
		sleep_p(philo, program);
		think(philo, program);
		meals++;
	}
	/* cleanup */
	// if (sem_close(program->sem) == -1)
	// 	perror("sem close 1 prog");
	// clear_philos(program->philos, program->n_philos, false);
	// free(program);
	// printf("philo %d finished...\n", philo->id);
	set_philo_finished(philo);
	return (NULL);
}
