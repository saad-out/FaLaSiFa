/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:27:06 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/07 02:28:42 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_philo_died(t_philo *philo)
{
	int	died;

	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	died = philo->died;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	return (died);
}

int	check_philo_finished(t_philo *philo)
{
	int	finished;

	if (check_program_error(philo->program))
		return (-1);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (-1);
	finished = philo->finished;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (-1);
	return (finished);
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
	elapsed = time - philo->last_meal;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (*err = 1, 0);
	return (elapsed);
}

__u_int	get_philo_last_meal(t_philo *philo)
{
	__u_int	last_meal;

	if (check_program_error(philo->program))
		return (0);
	if (safe_sem(philo->sem, WAIT, philo->program) == -1)
		return (0);
	last_meal = philo->last_meal;
	if (safe_sem(philo->sem, POST, philo->program) == -1)
		return (0);
	return (last_meal);
}
