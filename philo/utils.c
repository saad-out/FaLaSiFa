/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/15 01:16:23 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_program_philo_died(t_program *program)
{
	int	ret;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	program->philo_died = true;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	check_program_philo_died(t_program *program)
{
	int		ret;
	bool	died;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	died = program->philo_died;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return ((int)died);
}

long	check_program_finished(t_program *program)
{
	int		ret;
	long	finished;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	finished = program->finished;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (finished);
}

int	set_program_finished(t_program *program)
{
	int	ret;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	program->finished++;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	check_program_ready(t_program *program)
{
	int		ret;
	bool	ready;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	ready = program->ready;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return ((int)ready);
}

int	set_program_ready(t_program *program)
{
	int	ret;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	program->ready = true;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	set_philo_last_meal(t_philo *philo)
{
	int	ret;

	ret = safe_mutex(&philo->mutex, LOCK, philo->program);
	if (ret == -1)
		return (-1);
	philo->last_meal = get_time();
	ret = safe_mutex(&philo->mutex, UNLOCK, philo->program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	set_philo_finished(t_philo *philo)
{
	int	ret;

	ret = safe_mutex(&philo->mutex, LOCK, philo->program);
	if (ret == -1)
		return (-1);
	philo->finished = true;
	ret = safe_mutex(&philo->mutex, UNLOCK, philo->program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	check_philo_finished(t_philo *philo)
{
	int	ret;
	bool	finished;

	ret = safe_mutex(&philo->mutex, LOCK, philo->program);
	if (ret == -1)
		return (-1);
	finished = philo->finished;
	ret = safe_mutex(&philo->mutex, UNLOCK, philo->program);
	if (ret == -1)
		return (-1);
	return ((int)finished);
}
