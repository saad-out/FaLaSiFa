/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:11:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 16:26:09 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	init_program(t_program *program, t_fork **fs, t_philo **ps)
{
	program->forks = fs;
	program->philos = ps;
	program->finished = false;
	program->ready = false;
	program->philo_died = false;
	program->err = false;
	if (pthread_mutex_init(&program->mutex, NULL) != 0)
	{
		ft_putendl_fd(MUTEX_INIT_ERROR, STDERR_FILENO);
		free(program);
		return (false);
	}
	if (pthread_mutex_init(&program->print_mutex, NULL) != 0)
	{
		ft_putendl_fd(MUTEX_INIT_ERROR, STDERR_FILENO);
		free(program);
		return (false);
	}
	return (true);
}

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_fork		**forks;
	t_philo		**philos;

	program = parse_input(ac, av);
	if (!program)
		return (ft_putendl_fd("wrong input", 2));
	forks = init_forks(program->n_philos);
	if (!forks)
	{
		ft_putendl_fd("error creating forks", STDERR_FILENO);
		return (free(program));
	}
	philos = init_philos(program, forks);
	if (!philos)
	{
		ft_putendl_fd("error creating philos", STDERR_FILENO);
		clear_forks(forks, program->n_philos);
		return (free(program));
	}
	if (!init_program(program, forks, philos))
		return ;
	start_threads(program);
	clear_forks(forks, program->n_philos);
	return (clear_philos(philos, program->n_philos), free(program));
}
