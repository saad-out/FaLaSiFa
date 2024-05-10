/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/10 16:19:57 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	*get_name(__u_int i)
{
	char	*id;
	char	*name;

	id = ft_itoa(i + 1);
	if (!id)
		return (ft_putendl_fd(MALLOC_ERROR, STDERR_FILENO), NULL);
	name = ft_strjoin(PHILO_SEM_NAME, id);
	if (!name)
		ft_putendl_fd(MALLOC_ERROR, STDERR_FILENO);
	free(id);
	return (name);
}

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

static t_philo	*init_philo(t_philo *philo, __u_int i, t_program *program)
{
	char	*colors[7];

	init_colors(colors);
	philo->id = i + 1;
	philo->program = program;
	philo->finished = 0;
	philo->died = 0;
	philo->pid = 0;
	philo->color = colors[i % 7];
	philo->last_meal = get_time();
	philo->name = get_name(i);
	if (!philo->name)
		return (free(philo), NULL);
	sem_unlink(philo->name);
	philo->sem = sem_open(philo->name, O_CREAT | O_EXCL, O_RDWR, 1);
	if (philo->sem == SEM_FAILED)
	{
		ft_putendl_fd(SEM_OPEN_ERROR, STDERR_FILENO);
		return (free(philo->name), free(philo), NULL);
	}
	return (philo);
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
		philos[i] = init_philo(philos[i], i, program);
		if (!philos[i])
			return (clear_philos(philos, i, true), NULL);
		i++;
	}
	return (philos);
}
