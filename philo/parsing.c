/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:53:48 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/15 01:57:27 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_program	*parse_input(int ac, char **av)
{
	t_program	*program;
	long		n;
	bool		err;
	int			ret;

	program = (t_program *)malloc(sizeof(t_program));
	if (!program)
	{
		ft_putendl_fd(MALLOC_ERROR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
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
	ret = pthread_mutex_init(&program->mutex, NULL);
	if (ret != 0)
		return (free(program), NULL);
	ret = pthread_mutex_init(&program->print_mutex, NULL);
	if (ret != 0)
		return (pthread_mutex_destroy(&program->mutex), free(program), NULL);
	return (program);
}
