/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:19:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/05 00:34:12 by soutchak         ###   ########.fr       */
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

	/*  debug */
	// printf("slm\n");
	// died = 0;
	// ret_value = malloc(sizeof(int));
	// *ret_value = 0;
	// if (!died)
	// 	return (printf("monitor thread %d ended\n", philo->id), (void *)ret_value);
	// printf("===========> monitor started %d\n", philo->id);

	/* delay pair */
	if (philo->id % 2 == 0)
		usleep(2 * 1000);
	/* delay from philo */
	usleep(2 * 1000);

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
			died = 1;
			sem_wait(program->print_lock);
			printf("%sphilo %d DIED (last meal => %u ms ago)%s\n",philo->color, philo->id, get_time() - philo->last_meal, RESET);
			// int val;
			// sem_getvalue(program->print_lock, &val);
			// printf("--------------- SEMVAL is %d\n", val);
			// write(1, "cant print\n", sizeof("cant print\n"));
			break ;
		}
		usleep(5 * 1000);
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

	/* return value */
	// if (died)
	// 	*ret_value = EXIT_FAILURE;
	// *ret_value = EXIT_SUCCESS;
	// printf("%s&&&&&&&&&&&& MONITOR %d GOING TO EXIT WITH %d%s\n",philo->color, philo->id, *ret_value, RESET);
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

	/* debug */
	// printf("slm2\n");
	// died = 0;
	// if (!died)
	// 	return (printf("philo thread %d ended\n", philo->id), NULL);
	// printf("=> philo %d\n", philo->id);

	/* delay pair */
	if (philo->id % 2 == 0)
		usleep(2 * 1000);

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
	// 	printf("==========> I AM %d DEAD\n", philo->id);
	return (NULL);
}
