/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:09 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 22:07:04 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_fork		**forks;
	t_philo		**philosophers;

	program = parse_input(ac, av);
	if (!program)
		return (printf("wrong input\n"), exit(EXIT_FAILURE));
	/**/
	forks = init_forks(program->n_philos);
	if (!forks)
		return (printf("malloc error\n"), free(program), exit(EXIT_FAILURE));
	/**/
	clear_forks(forks, program->n_philos);
	free(program);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("wrong input\n"), exit(EXIT_FAILURE), 1);
	philosophers(ac - 1, av + 1);
	return (0);
}
