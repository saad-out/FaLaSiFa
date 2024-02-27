/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:55:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 22:12:22 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
