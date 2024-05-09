/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:52:09 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/08 18:54:33 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	philo_dead(t_program *program)
{
	int		i;
	bool	died;
	__u_int	time;

	i = 0;
	died = false;
	while (i < program->n_philos && !died)
	{
		if (check_philo_finished(program->philos[i]) == 0)
		{
			safe_mutex(&program->philos[i]->mutex, LOCK, program);
			time = get_time();
			if (program->philos[i]->last_meal <= time - program->t_die)
			{
				set_program_philo_died(program);
				died = true;
				safe_mutex(&program->print_mutex, LOCK, program);
				print_dead(program->philos[i]);
				safe_mutex(&program->print_mutex, UNLOCK, program);
			}
			safe_mutex(&program->philos[i]->mutex, UNLOCK, program);
		}
		i++;
	}
	return (died);
}

void	*monitor_thread(void *arg)
{
	t_program	*program;

	if (!arg)
		return (NULL);
	program = (t_program *)arg;
	while (check_program_ready(program) == 0)
	{
	}
	ft_usleep(2);
	while (true)
	{
		if (philo_dead(program))
			break ;
		if (check_program_finished(program) == program->n_philos)
			break ;
		ft_usleep(5);
	}
	return (NULL);
}
