/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:54:29 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 10:26:43 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_program	*set_max_meals(t_program *program, char *av)
{
	bool	err;

	if (av)
	{
		err = 0;
		program->max_meals = (long)ft_atoerr(av, &err);
		if (err)
			return (free(program), NULL);
	}
	else
		program->max_meals = -1;
	return (program);
}

t_program	*parse_input(int ac, char **av)
{
	t_program	*program;
	bool		err;

	(void)ac;
	program = (t_program *)malloc(sizeof(t_program));
	if (!program)
		return (printf("malloc error\n"), exit(EXIT_FAILURE), NULL);
	err = 0;
	program->n_philos = ft_atoerr(av[0], &err);
	if (err)
		return (free(program), NULL);
	program->t_die = ft_atoerr(av[1], &err);
	if (err)
		return (free(program), NULL);
	program->t_eat = ft_atoerr(av[2], &err);
	if (err)
		return (free(program), NULL);
	program->t_sleep = ft_atoerr(av[3], &err);
	if (err)
		return (free(program), NULL);
	return (set_max_meals(program, av[4]));
}
