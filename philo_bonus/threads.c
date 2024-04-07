/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 21:19:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/07 01:55:35 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	print_died(t_philo *philo)
{
	printf("%s%u %d died%s\n", philo->color, get_time(), philo->id, RESET);
}

static bool	track_philo(t_philo *philo, t_program *program)
{
	bool	died;
	bool	err;
	__u_int	time;

	died = false;
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
			print_died(philo);
			died = 1;
			break ;
		}
		ft_usleep(5);
	}
	return (died);
}

void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	bool		died;
	int			*ret_value;

	philo = (t_philo *)arg;
	program = philo->program;
	ft_usleep(5);
	died = track_philo(philo, program);
	ret_value = malloc(sizeof(int));
	if (!ret_value)
	{
		ft_putendl_fd(MALLOC_ERROR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (died)
		*ret_value = EXIT_FAILURE;
	else
		*ret_value = EXIT_SUCCESS;
	return ((void *)ret_value);
}

static void	simulation(t_philo *philo, t_program *program)
{
	long		meals;

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
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	program = philo->program;
	if (set_philo_last_meal(philo) == -1)
		return (NULL);
	if (philo->id % 2 == 0)
		ft_usleep(50);
	simulation(philo, program);
	if (check_philo_died(philo) != 1)
		set_philo_finished(philo);
	return (NULL);
}
