/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:31:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 01:53:22 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_program_error(t_program *program)
{
	// sem_wait(program->sem);
	program->error = true;
	// sem_post(program->sem);
}

int	check_program_error(t_program *program)
{
	int	err;

	if (sem_wait(program->var_lock) == -1)
		return (set_program_error(program), 1);
	err = program->error;
	if (sem_post(program->var_lock) == -1)
		return (set_program_error(program), 1);
	return (err);
}

int	safe_sem(sem_t *sem, int action, t_program *program)
{
	int	ret;

	if (!sem)
		return (set_program_error(program), -1);
	ret = -1;
	if (action == POST)
		ret = sem_post(sem);
	else if (action == WAIT)
		ret = sem_wait(sem);
	if (ret == -1)
	{
		ft_putendl_fd("safe_sem() error", STDERR_FILENO);
		set_program_error(program);
		return (-1);
	}
	return (0);
}

void	kill_all_except(t_philo **philos, __u_int n, pid_t exception)
{
	// printf("killing all except %d\n", exception);
	for (__u_int i = 0; i < n; i++)
	{
		if (philos[i]->pid != exception)
			kill(philos[i]->pid, SIGKILL);
	}
}
