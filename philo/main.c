/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:09 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/15 01:53:57 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_fork		**forks;
	t_philo		**philos;

	/* parsing */
	program = parse_input(ac, av);
	if (!program)
		return (ft_putendl_fd("wrong input", 2), exit(EXIT_FAILURE));
	/* ------ */

	/* init */
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
	program->forks = forks;
	program->philos = philos;
	program->finished = false;
	program->ready = false;
	program->philo_died = false;
	program->err = false;
	/* -- */

	/* core */
	start_threads(program);
	/* --- */

	/* cleanup */
	clear_forks(forks, program->n_philos);
	clear_philos(philos, program->n_philos);
	free(program);
	/* ----- */
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_putendl_fd("wrong input", STDERR_FILENO), EXIT_FAILURE);
	philosophers(ac - 1, av + 1);
	return (0);
}
