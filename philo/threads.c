/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:51:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/16 22:42:22 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	create_threads(t_program *pg, t_philo **ps, t_fork **fs)
{
	__u_int	i;
	int		ret;

	i = 0;
	while (i < pg->n_philos)
	{
		ret = pthread_create(&ps[i]->thread, NULL, philo_thread, (void *)ps[i]);
		if (ret != 0)
			return (ft_putendl_fd(PTHREAD_CREATE_ERROR, STDERR_FILENO), 0);
		i++;
	}
	ret = pthread_create(&pg->monitor, NULL, monitor_thread, (void *)pg);
	if (ret != 0)
		return (ft_putendl_fd(PTHREAD_CREATE_ERROR, STDERR_FILENO), 0);
	return (1);
}

static void	join_threads(t_program *pg, t_philo **ps, t_fork **fs)
{
	__u_int	i;
	int		ret;

	i = 0;
	while (i < pg->n_philos)
	{
		ret = pthread_join(ps[i]->thread, NULL);
		if (ret != 0)
			return (ft_putendl_fd(PTHREAD_JOIN_ERROR, STDERR_FILENO));
		i++;
	}
	ret = pthread_join(pg->monitor, NULL);
	if (ret != 0)
		return (ft_putendl_fd(PTHREAD_JOIN_ERROR, STDERR_FILENO));
}

void	start_threads(t_program *program)
{
	t_philo	**philos;
	t_fork	**forks;

	philos = program->philos;
	forks = program->forks;
	if (!create_threads(program, philos, forks))
		return ;
	if (set_program_ready(program) == -1)
		return ;
	return (join_threads(program, philos, forks));
}
