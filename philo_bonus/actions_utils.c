/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:36:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/07 00:37:15 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	get_first_fork(t_philo *philo, t_program *program)
{
	char	*color;
	int		id;

	if (check_program_error(program))
		return (0);
	if (safe_sem(program->forks, WAIT, program) == -1)
		return (0);
	if (check_program_error(program) || check_philo_died(philo) == 1)
		return (0);
	safe_sem(program->print_lock, WAIT, program);
	color = philo->color;
	id = philo->id;
	printf("%s%u %d has taken a fork%s\n", color, get_time(), id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	if (program->n_philos == 1)
	{
		while (check_philo_died(philo) != 1)
			ft_usleep(60);
		return (0);
	}
	return (1);
}

bool	get_second_fork(t_philo *philo, t_program *program)
{
	char	*color;
	int		id;

	if (check_program_error(program))
		return (0);
	if (safe_sem(program->forks, WAIT, program) == -1)
		return (0);
	if (check_program_error(program) || check_philo_died(philo) == 1)
		return (0);
	safe_sem(program->print_lock, WAIT, program);
	color = philo->color;
	id = philo->id;
	printf("%s%u %d has taken a fork%s\n", color, get_time(), id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	return (1);
}
