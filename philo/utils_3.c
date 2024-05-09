/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:20:16 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 16:11:28 by soutchak         ###   ########.fr       */
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

int	set_program_finished(t_program *program)
{
	if (safe_mutex(&program->mutex, LOCK, program) == -1)
		return (-1);
	program->finished++;
	if (safe_mutex(&program->mutex, UNLOCK, program) == -1)
		return (-1);
	return (0);
}
