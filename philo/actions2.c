/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:29:34 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/08 18:52:04 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	get_first_fork(t_philo *philo, t_program *program)
{
	bool	end;

	safe_mutex(&philo->program->mutex, LOCK, program);
	end = program->err || program->philo_died;
	safe_mutex(&philo->program->mutex, UNLOCK, program);
	if (end)
		return (false);
	safe_mutex(&philo->first_fork->mutex, LOCK, program);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_fork(philo);
	if (program->n_philos == 1)
		return (ft_usleep(program->t_die + 5), false);
	return (true);
}

bool	get_second_fork(t_philo *philo, t_program *program)
{
	bool	end;

	safe_mutex(&philo->program->mutex, LOCK, program);
	end = program->err || program->philo_died;
	safe_mutex(&philo->program->mutex, UNLOCK, program);
	if (end)
		return (false);
	safe_mutex(&philo->second_fork->mutex, LOCK, program);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_fork(philo);
	if (program->n_philos == 1)
		return (ft_usleep(program->t_die + 5), false);
	return (true);
}
