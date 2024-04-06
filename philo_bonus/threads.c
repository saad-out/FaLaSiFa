/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:19:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 03:48:41 by soutchak         ###   ########.fr       */
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
	bool		err;

	/* init */
	philo = (t_philo *)arg;
	program = philo->program;
	died = 0;

	/* delay pair */
	if (philo->id % 2 == 0)
		ft_usleep(2);
	/* delay from philo */
	ft_usleep(2);

	/* core */
	while (!died)
	{
		if (check_philo_finished(philo) != 0)
			break ;
		err = 0;
		time = get_time_since_last_meal(philo, &err);
		if (err)
			break ;
		if (time >= program->t_die)
		{
			set_philo_died(philo);
			sem_wait(program->print_lock);
			// printf("%sphilo %d DIED (last meal => %u ms ago)%s\n",philo->color, philo->id, get_time() - philo->last_meal, RESET);
			printf("%s%u %d died%s\n",philo->color, get_time(), philo->id, RESET);
			died = 1;
			// kill(getpid(), SIGKILL);
			break ;
		}
		ft_usleep(5);
	}
	// if (died)
	// 	printf("======> MONITOR %d says dead\n", philo->id);
	ret_value = malloc(sizeof(int));
	if (!ret_value)
		return (ft_putendl_fd("error malloc()", 2), (void *)EXIT_FAILURE); //TODO: wrong as ret is not allocated
	if (died)
		*ret_value = EXIT_FAILURE;
	else
		*ret_value = EXIT_SUCCESS;

	return ((void *)ret_value);
}

void*	philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	long		meals;

	/* init */
	philo = (t_philo *)arg;
	program = philo->program;
	meals = 0;
	// printf("*************dkhl%d\n", philo->id);
	if (set_philo_last_meal(philo) == -1)
		return (NULL);

	/* delay pair */
	if (philo->id % 2 == 0)
		ft_usleep(50);

	/* core */
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
	if (check_philo_died(philo) != 1)
		set_philo_finished(philo);
	// else
	// 	printf("%s==========> I AM %d DEAD%s\n", philo->color, philo->id, RESET);
	return (NULL);
}