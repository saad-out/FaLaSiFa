/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:29:34 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/11 14:59:13 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	get_first_fork(t_philo *philo, t_program *program)
{
	bool	end;

	if (safe_mutex(&philo->program->mutex, LOCK, program) == -1)
		return (false);
	end = program->err || program->philo_died;
	if (safe_mutex(&philo->program->mutex, UNLOCK, program) == -1)
		return (false);
	if (end)
		return (false);
	if (safe_mutex(&philo->first_fork->mutex, LOCK, program) == -1)
		return (false);
	if (check_program_philo_died(program) != 0)
	{
		safe_mutex(&philo->first_fork->mutex, UNLOCK, program);
		safe_mutex(&philo->second_fork->mutex, UNLOCK, program);
		return (false);
	}
	print_fork(philo);
	if (program->n_philos == 1)
		return (ft_usleep(program->t_die + 5), false);
	return (true);
}

bool	get_second_fork(t_philo *philo, t_program *program)
{
	bool	end;

	if (safe_mutex(&philo->program->mutex, LOCK, program) == -1)
		return (false);
	end = program->err || program->philo_died;
	if (safe_mutex(&philo->program->mutex, UNLOCK, program) == -1)
		return (false);
	if (end)
		return (false);
	if (safe_mutex(&philo->second_fork->mutex, LOCK, program) == -1)
		return (false);
	if (check_program_philo_died(program) != 0)
	{
		safe_mutex(&philo->second_fork->mutex, UNLOCK, program);
		safe_mutex(&philo->first_fork->mutex, UNLOCK, program);
		return (false);
	}
	print_fork(philo);
	if (program->n_philos == 1)
		return (ft_usleep(program->t_die + 5), false);
	return (true);
}
