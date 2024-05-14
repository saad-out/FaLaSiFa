/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:55:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/11 14:59:52 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_colors(char **colors)
{
	colors[0] = RED;
	colors[1] = GRN;
	colors[2] = YEL;
	colors[3] = BLU;
	colors[4] = MAG;
	colors[5] = CYN;
	colors[6] = WHT;
}

static void	init_philo(int i, t_program *program, t_fork **fs, t_philo **philos)
{
	char	*colors[7];

	init_colors(colors);
	philos[i]->id = i + 1;
	philos[i]->color = colors[i % 7];
	philos[i]->program = program;
	philos[i]->finished = false;
	philos[i]->first_fork = fs[(i + 1) % program->n_philos];
	philos[i]->second_fork = fs[i];
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
		init_philo(i, program, forks, philos);
		ret = pthread_mutex_init(&philos[i]->mutex, NULL);
		if (ret != 0)
		{
			ft_putendl_fd(MUTEX_INIT_ERROR, STDERR_FILENO);
			return (clear_philos(philos, i), free(philos), NULL);
		}
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
		{
			ft_putendl_fd(MUTEX_INIT_ERROR, STDERR_FILENO);
			return (clear_forks(forks, i), free(forks), NULL);
		}
		i++;
	}
	return (forks);
}
