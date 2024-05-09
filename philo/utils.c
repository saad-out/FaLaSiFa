/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 15:25:34 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_program_ready(t_program *program)
{
	safe_mutex(&program->mutex, LOCK, program);
	program->ready = true;
	safe_mutex(&program->mutex, UNLOCK, program);
	return (0);
}

int	set_philo_last_meal(t_philo *philo)
{
	safe_mutex(&philo->mutex, LOCK, philo->program);
	philo->last_meal = get_time();
	safe_mutex(&philo->mutex, UNLOCK, philo->program);
	return (0);
}

int	set_philo_finished(t_philo *philo)
{
	safe_mutex(&philo->mutex, LOCK, philo->program);
	philo->finished = true;
	safe_mutex(&philo->mutex, UNLOCK, philo->program);
	return (0);
}

int	check_philo_finished(t_philo *philo)
{
	bool	finished;

	safe_mutex(&philo->mutex, LOCK, philo->program);
	finished = philo->finished;
	safe_mutex(&philo->mutex, UNLOCK, philo->program);
	return ((int)finished);
}

int	check_program_ready(t_program *program)
{
	bool	ready;

	safe_mutex(&program->mutex, LOCK, program);
	ready = program->ready;
	safe_mutex(&program->mutex, UNLOCK, program);
	return ((int)ready);
}
