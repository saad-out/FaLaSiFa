/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/11 14:55:31 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	check_program_philo_died(t_program *program)
{
	bool	died;

	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	died = program->philo_died;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return ((int)died);
}

long	check_program_finished(t_program *program)
{
	long	finished;

	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	finished = program->finished;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return (finished);
}
