/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:40:41 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/05 19:59:42 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	simulation(t_program *program, t_philo *philo)
{
	long		meals;

	if (philo->id % 2 == 0)
		ft_usleep(10);
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

static int	wait_threads(t_program *program)
{
	int			ret;

	ret = 0;
	while (!ret)
	{
		ret = check_program_ready(program);
		if (ret == -1)
			return (0);
	}
	return (1);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;
	bool		died;

	if (!arg)
		return (NULL);
	philo = (t_philo *)arg;
	program = philo->program;
	if (!wait_threads(program))
		return (NULL);
	if (set_philo_last_meal(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		return (pthread_mutex_unlock(&program->mutex), NULL);
	}
	simulation(program, philo);
	if (set_program_finished(program) == -1 || set_philo_finished(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		pthread_exit(NULL);
	}
	return (NULL);
}
