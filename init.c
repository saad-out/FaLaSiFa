/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:55:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/04 18:41:17 by soutchak         ###   ########.fr       */
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
	{
		pthread_mutex_destroy(&philos[j]->mutex);
		free(philos[j++]);
	}
	free(philos);
}

void	clear_forks(t_fork	**forks, __u_int i)
{
	__u_int	j;

	if (!forks)
		return ;
	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&forks[j]->mutex);
		free(forks[j++]);
	}
	free(forks);
}

t_philo	**init_philos(t_program *program, t_fork **forks)
{
	t_philo	**philos;
	__u_int	i;
	int		ret;

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
		philos[i]->finished = false;
		// if (i + 1 != program->n_philos)
		// {
		// 	philos[i]->first_fork = forks[i + 1];
		// 	philos[i]->second_fork = forks[i];
		// }
		// else
		// {
		// 	philos[i]->first_fork = forks[i];
		// 	philos[i]->second_fork = forks[(i + 1) % program->n_philos];
		// }
		philos[i]->first_fork = forks[(i + 1) % program->n_philos];
		philos[i]->second_fork = forks[i];
		ret = pthread_mutex_init(&philos[i]->mutex, NULL);
		if (ret != 0)
			return (clear_philos(philos, i), free(philos), NULL);
		i++;
	}
	return (philos);
}

t_fork	**init_forks(__u_int n)
{
	t_fork	**forks;
	__u_int	i;
	int		ret;

	forks = malloc(sizeof(t_fork *) * n);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n)
	{
		forks[i] = malloc(sizeof(t_fork));
		if (!forks[i])
			return (clear_forks(forks, i), free(forks), NULL);
		forks[i]->id = i;
		ret = pthread_mutex_init(&forks[i]->mutex, NULL);
		if (ret != 0)
			return (clear_forks(forks, i), free(forks), NULL);
		i++;
	}
	return (forks);
}
