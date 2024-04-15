/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:58:42 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/15 02:39:00 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	eat(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	if (!philo)
		return (false);
	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	end = program->err || program->philo_died;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (false);
	if (end)
		return (false);
	if (set_philo_last_meal(philo) == -1)
		return (set_program_error(program), false);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_eating(philo);
	ft_usleep(program->t_eat);
	return (true);
}

bool	sleep_p(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	if (!philo)
		return (false);
	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	end = program->err || program->philo_died;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (false);
	if (end)
		return (false);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_sleeping(philo);
	ft_usleep(program->t_sleep);
	return (true);
}

bool	think(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	if (!philo)
		return (false);
	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	end = program->err || program->philo_died;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (false);
	if (end)
		return (false);
	if (check_program_philo_died(program) == 1)
		return (false);
	print_thinking(philo);
	return (true);
}

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

bool	get_forks(t_philo *philo, t_program *program)
{
	return (get_first_fork(philo, program) && get_second_fork(philo, program));
}

bool	put_forks(t_philo *philo, t_program *program)
{
	int	ret;
	int	end;

	safe_mutex(&philo->first_fork->mutex, UNLOCK, program);
	safe_mutex(&philo->second_fork->mutex, UNLOCK, program);
	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (false);
	end = program->err || program->philo_died;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (false);
	if (end)
		return (false);
	return (true);
}
