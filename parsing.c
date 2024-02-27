/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:53:48 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 21:54:09 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_program	*parse_input(int ac, char **av)
{
	t_program	*program;
	long		n;
	bool		err;

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
	if (av[4])
	{
		program->max_meals = (long)ft_atoerr(av[4], &err);
		if (err)
			return (free(program), NULL);
	}
	else
		program->max_meals = -1;
	return (program);
}
