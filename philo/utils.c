/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 16:13:47 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_program_ready(t_program *program)
{
	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	program->ready = true;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return (0);
}

int	set_philo_last_meal(t_philo *philo)
{
	if (safe_mutex(&philo->mutex, LOCK, philo->program) == -1)
		return (-1);
	philo->last_meal = get_time();
	if (safe_mutex(&philo->mutex, UNLOCK, philo->program) == -1)
		return (-1);
	return (0);
}

int	set_philo_finished(t_philo *philo)
{
	if (safe_mutex(&philo->mutex, LOCK, philo->program) == -1)
		return (-1);
	philo->finished = true;
	if (safe_mutex(&philo->mutex, UNLOCK, philo->program) == -1)
		return (-1);
	return (0);
}

int	check_philo_finished(t_philo *philo)
{
	bool	finished;

	if (safe_mutex(&philo->mutex, LOCK, philo->program) == -1)
		return (-1);
	finished = philo->finished;
	if (safe_mutex(&philo->mutex, UNLOCK, philo->program) == -1)
		return (-1);
	return ((int)finished);
}

int	check_program_ready(t_program *program)
{
	bool	ready;

	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	ready = program->ready;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return ((int)ready);
}
