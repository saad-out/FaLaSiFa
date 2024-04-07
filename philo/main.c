/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:09 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/04 16:03:01 by soutchak         ###   ########.fr       */
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
		return (printf("wrong input\n"), exit(EXIT_FAILURE));
	/* ------ */

	/* init */
	forks = init_forks(program->n_philos);
	if (!forks)
		return (printf("malloc error\n"), free(program), exit(EXIT_FAILURE));
	philos = init_philos(program, forks);
	if (!philos)
	{
		printf("malloc error\n");
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
	// start_threads(program, philos, forks);
	start_threads(program);
	/* --- */

	/* cleanup */
	printf("reached cleanup\n");
	clear_forks(forks, program->n_philos);
	clear_philos(philos, program->n_philos);
	free(program);
	/* ----- */
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("wrong input\n"), exit(EXIT_FAILURE), 1);
	philosophers(ac - 1, av + 1);
	return (0);
}
