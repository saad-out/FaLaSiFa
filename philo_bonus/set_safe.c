/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_safe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/07 02:29:33 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	set_philo_died(t_philo *philo)
{
	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	philo->died = true;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	return (0);
}

int	set_philo_finished(t_philo *philo)
{
	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	philo->finished = true;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	return (0);
}

int	set_philo_last_meal(t_philo *philo)
{
	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	philo->last_meal = get_time();
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	return (0);
}
