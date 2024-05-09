/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:52:09 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 22:49:08 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	died_since_last_meal(t_program *program, __u_int i)
{
	__u_int	time;
	bool	died;

	died = false;
	if (safe_mutex(&program->philos[i]->mutex, LOCK, program) == -1)
		return (-1);
	time = get_time();
	if (program->t_die <= time - program->philos[i]->last_meal)
	{
		if (set_program_philo_died(program) == -1)
			return (-1);
		died = true;
		if (safe_mutex(&program->print_mutex, LOCK, program) == -1)
			return (-1);
		print_dead(program->philos[i]);
		if (safe_mutex(&program->print_mutex, UNLOCK, program) == -1)
			return (-1);
	}
	if (safe_mutex(&program->philos[i]->mutex, UNLOCK, program) == -1)
		return (-1);
	return ((int)died);
}

int	philo_dead(t_program *program)
{
	__u_int	i;
	bool	died;
	int		ret;

	i = 0;
	died = false;
	while (i < program->n_philos && !died)
	{
		ret = check_philo_finished(program->philos[i]);
		if (ret == -1)
			return (-1);
		if (ret == 0)
		{
			if (died_since_last_meal(program, i) != 0)
				died = true;
		}
		i++;
	}
	return (died);
}

void	*monitor_thread(void *arg)
{
	t_program	*program;
	int			ret;

	if (!arg)
		return (NULL);
	program = (t_program *)arg;
	if (!wait_threads(program))
		return (NULL);
	ft_usleep(2);
	while (true)
	{
		if (philo_dead(program) != 0)
			break ;
		ret = check_program_finished(program);
		if (ret == -1 || ret == (int)program->n_philos)
			return (NULL);
		ft_usleep(5);
	}
	return (NULL);
}
