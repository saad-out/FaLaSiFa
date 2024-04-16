/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:11:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/16 22:15:02 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_program(t_program *program, t_fork **fs, t_philo **ps)
{
	program->forks = fs;
	program->philos = ps;
	program->finished = false;
	program->ready = false;
	program->philo_died = false;
	program->err = false;
}

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_fork		**forks;
	t_philo		**philos;

	program = parse_input(ac, av);
	if (!program)
		return (ft_putendl_fd("wrong input", 2), exit(EXIT_FAILURE));
	forks = init_forks(program->n_philos);
	if (!forks)
	{
		ft_putendl_fd("error creating forks", STDERR_FILENO);
		return (free(program), exit(EXIT_FAILURE));
	}
	philos = init_philos(program, forks);
	if (!philos)
	{
		ft_putendl_fd("error creating philos", STDERR_FILENO);
		clear_forks(forks, program->n_philos);
		return (free(program), exit(EXIT_FAILURE));
	}
	init_program(program, forks, philos);
	start_threads(program);
	clear_forks(forks, program->n_philos);
	clear_philos(philos, program->n_philos);
	free(program);
}