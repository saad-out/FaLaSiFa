/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:40:41 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/16 22:41:20 by soutchak         ###   ########.fr       */
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
			return (NULL);
	}
	if (set_philo_last_meal(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		return (NULL);
	}
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
	if (set_program_finished(program) == -1 || set_philo_finished(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		pthread_exit(NULL);
	}
	return (NULL);
}