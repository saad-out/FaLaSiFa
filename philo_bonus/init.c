/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/07 00:21:19 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	clear_philos(t_philo **philos, __u_int i)
{
	__u_int	j;

	if (!philos)
		return ;
	j = 0;
	while (j < i)
		free(philos[j++]);
	free(philos);
}

t_philo	**init_philos(t_program *program)
{
	t_philo	**philos;
	__u_int	i;

	philos = malloc(sizeof(t_philo *) * program->n_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < program->n_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (clear_philos(philos, i), free(philos), NULL);
		philos[i]->id = i + 1;
		philos[i]->program = program;
		philos[i]->finished = 0;

		philos[i]->sem = program->sem;
		i++;
	}
	return (philos);
}
