/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 23:39:54 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	clear_philos(t_philo **philos, __u_int i, bool parent)
{
	__u_int	j;

	printf("===> clear philos parent=%d\n", parent);
	if (!philos)
		return ;
	j = 0;
	while (j < i)
	{
		if (sem_close(philos[j]->sem) == -1)
			perror("sem close 2");
		if (parent && sem_unlink(philos[j]->name) == -1)
			perror("sem unlink 2");
		free(philos[j]->name);
		free(philos[j]);
		j++;
	}
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
			return (clear_philos(philos, i, true), NULL);
		philos[i]->id = i + 1;
		philos[i]->program = program;
		philos[i]->finished = 0;
		philos[i]-> died = 0;

		// philos[i]->sem = program->sem;
		char	*id = ft_itoa(i + 1);
		char	*name = ft_strjoin(PHILO_SEM_NAME, id);
		philos[i]->name = name;
		free(id);
		philos[i]->sem = sem_open(philos[i]->name, O_CREAT | O_EXCL, 1);
		if (philos[i]->sem == SEM_FAILED)
			return (perror("sem1"), printf("error creating semaphor ph\n"), clear_philos(philos, i, true), NULL);
		printf("opened sem %s\n", philos[i]->name);
		i++;
	}
	return (philos);
}
