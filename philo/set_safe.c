/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_safe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:20:16 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 18:43:19 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_program_philo_died(t_program *program)
{
	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	program->philo_died = true;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return (0);
}

int	set_program_finished(t_program *program)
{
	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	program->finished++;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return (0);
}

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
