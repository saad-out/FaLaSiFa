/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/04 22:49:44 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_program_philo_died(t_program *program)
{
	int	died;

	if (check_program_error(program))
		return (-1);
	if (safe_sem(program->var_lock, WAIT, program) == -1)
		return (-1);
	// printf("waited\n");
	died = program->philo_died;
	if (safe_sem(program->var_lock, POST, program) == -1)
		return (-1);
	// printf("posted\n");
	return (died);
}

int	set_program_philo_died(t_program *program)
{
	if (check_program_error(program))
		return (-1);
	if (safe_sem(program->var_lock, WAIT, program) == -1)
		return (-1);
	// printf("waited\n");
	program->philo_died = true;
	if (safe_sem(program->var_lock, POST, program) == -1)
		return (-1);
	// printf("posted\n");
	return (0);
}

int	check_philo_died(t_philo *philo)
{
	int	died;

	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	// printf("waited\n");
	died = philo->died;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	// printf("posted\n");
	return (died);
}

int	set_philo_died(t_philo *philo)
{
	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	// printf("waited\n");
	philo->died = true;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	// printf("posted\n");
	return (0);
}

int	check_philo_finished(t_philo *philo)
{
	int	finished;

	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	// printf("waited\n");
	finished = philo->finished;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	// printf("posted\n");
	return (finished);
}

int	set_philo_finished(t_philo *philo)
{
	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	// printf("waited\n");
	philo->finished = true;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	// printf("posted\n");
	return (0);
}

__u_int	get_philo_last_meal(t_philo *philo)
{
	__u_int	last_meal;

	if (check_program_error(philo->program))
		return (0);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (0);
	// printf("waited\n");
	last_meal = philo->last_meal;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (0);
	// printf("posted\n");
	return (last_meal);
}

int	set_philo_last_meal(t_philo *philo)
{
	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	// printf("waited\n");
	philo->last_meal = get_time();
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	// printf("posted\n");
	return (0);
}

__u_int	get_time_since_last_meal(t_philo *philo, bool *err)
{
	__u_int	time;
	__u_int	elapsed;

	*err = 0;
	if (check_program_error(philo->program))
		return (*err = 1, 0);
	time = get_time();
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (*err = 1, 0);
	// printf("waited\n");
	elapsed = time - philo->last_meal;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (*err = 1, 0);
	// printf("posted\n");
	return (elapsed);
}
