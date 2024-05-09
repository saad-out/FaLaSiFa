/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:20:16 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 15:25:26 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_program_philo_died(t_program *program)
{
	safe_mutex(&program->mutex, LOCK, program);
	program->philo_died = true;
	safe_mutex(&program->mutex, UNLOCK, program);
	return (0);
}

int	check_program_philo_died(t_program *program)
{
	bool	died;

	safe_mutex(&program->mutex, LOCK, program);
	died = program->philo_died;
	safe_mutex(&program->mutex, UNLOCK, program);
	return ((int)died);
}

long	check_program_finished(t_program *program)
{
	long	finished;

	safe_mutex(&program->mutex, LOCK, program);
	finished = program->finished;
	safe_mutex(&program->mutex, UNLOCK, program);
	return (finished);
}

int	set_program_finished(t_program *program)
{
	safe_mutex(&program->mutex, LOCK, program);
	program->finished++;
	safe_mutex(&program->mutex, UNLOCK, program);
	return (0);
}
