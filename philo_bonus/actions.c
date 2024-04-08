/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:12:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/08 15:41:53 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	eat(t_philo *philo, t_program *program)
{
	char	*color;
	int		id;

	if (check_program_error(program))
		return (0);
	if (check_philo_died(philo) == 1)
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	id = philo->id;
	color = philo->color;
	printf("%s%u %d is eating%s\n", color, get_time(), id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	if (set_philo_last_meal(philo) == -1)
		return (ft_putendl_fd("Error setting last meal time", 2), 0);
	ft_usleep(program->t_eat);
	return (1);
}

bool	think(t_philo *philo, t_program *program)
{
	char	*color;
	int		id;

	if (check_program_error(program))
		return (0);
	if (check_philo_died(philo) == 1)
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	id = philo->id;
	color = philo->color;
	printf("%s%u %d is thinking%s\n", color, get_time(), id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	ft_usleep(THINK_TIME);
	return (1);
}

bool	sleep_p(t_philo *philo, t_program *program)
{
	char	*color;
	int		id;

	if (check_program_error(program))
		return (0);
	if (check_philo_died(philo) == 1)
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	id = philo->id;
	color = philo->color;
	printf("%s%u %d is sleeping%s\n", color, get_time(), id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	ft_usleep(program->t_sleep);
	return (1);
}

bool	put_forks(t_philo *philo, t_program *program)
{
	if (check_program_error(program))
		return (0);
	if (safe_sem(program->forks, POST, program) == -1)
		return (0);
	if (check_program_error(program) || check_philo_died(philo) == 1)
		return (0);
	if (safe_sem(program->forks, POST, program) == -1)
		return (0);
	if (check_program_error(program) || check_philo_died(philo) == 1)
		return (0);
	return (1);
}

bool	get_forks(t_philo *philo, t_program *program)
{
	return (get_first_fork(philo, program) && get_second_fork(philo, program));
}
