/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:29:34 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/07 00:30:10 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	get_first_fork(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	ret = safe_mutex(&philo->program->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	end = program->err || program->philo_died;
	ret = safe_mutex(&philo->program->mutex, UNLOCK, program);
	if (ret == -1)
		return (false);
	if (end)
		return (false);
	ret = safe_mutex(&philo->first_fork->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_fork(philo);
	if (philo->program->n_philos == 1)
	{
		while (check_program_philo_died(program) != 1)
			ft_usleep(program->t_die);
		return (false);
	}
	return (true);
}

bool	get_second_fork(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	ret = safe_mutex(&philo->program->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	end = program->err || program->philo_died;
	ret = safe_mutex(&philo->program->mutex, UNLOCK, program);
	if (ret == -1)
		return (false);
	if (end)
		return (false);
	ret = safe_mutex(&philo->second_fork->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_fork(philo);
	return (true);
}
