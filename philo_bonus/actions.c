/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:12:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/05 00:04:07 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	eat(t_philo *philo, t_program *program)
{
	if (check_program_error(program) || check_philo_died(philo))
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d started eating (last meal => %u ms ago)%s\n",philo->color, philo->id, get_time() - philo->last_meal, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	if (set_philo_last_meal(philo) == -1)
		return (perror("eat sem\n"), 0);
	usleep(program->t_eat * 1000);
	return (1);
}

bool	think(t_philo *philo, t_program *program)
{
	if (check_program_error(program) || check_philo_died(philo))
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d is thinking%s\n", philo->color, philo->id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	// force thinking to avoid starvation
	usleep(THINK_TIME * 1000);
	return (1);
}

bool	sleep_p(t_philo *philo, t_program *program)
{
	if (check_program_error(program) || check_philo_died(philo))
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d is sleeping%s\n", philo->color, philo->id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	usleep(program->t_sleep * 1000);
	return (1);
}

bool	put_forks(t_philo *philo, t_program *program)
{
	if (check_program_error(program) || check_philo_died(philo))
		return (0);

	/*FIRST FORK*/
	if (safe_sem(program->forks, POST, program) == -1)
		return (0);

	if (check_program_error(program) || check_philo_died(philo))
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d PUT first fork%s\n",philo->color,	philo->id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);

	/* SECOND FORK */
	if (safe_sem(program->forks, POST, program) == -1)
		return (0);
	
	if (check_program_error(program) || check_philo_died(philo))
		return (0);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d PUT second fork%s\n",philo->color, philo->id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	return (1);
}

bool	get_forks(t_philo *philo, t_program *program)
{
	if (check_program_error(program) || check_philo_died(philo))
		return (0);

	/*FIRST FORK*/
	// printf("let's get first fork %d\n", philo->id);
	if (safe_sem(program->forks, WAIT, program) == -1)
		return (0);

	if (check_program_error(program) || check_philo_died(philo))
		return (0);
		// return (printf("kayn mochkil\n"), 0);
	// printf("chdha %d\n", philo->id);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d HAS TAKEN first fork%s\n",philo->color, philo->id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);

	/* SECOND FORK */
	// printf("let's get second fork %d\n", philo->id);
	if (safe_sem(program->forks, WAIT, program) == -1)
		return (0);
	
	if (check_program_error(program) || check_philo_died(philo))
		return (0);
		// return (printf("kayn mochkil\n"), 0);
	// printf("chdha %d\n", philo->id);
	if (safe_sem(program->print_lock, WAIT, program) == -1)
		return (0);
	printf("%sphilo %d HAS TAKEN second fork%s\n",philo->color, philo->id, RESET);
	if (safe_sem(program->print_lock, POST, program) == -1)
		return (0);
	return (1);
}
