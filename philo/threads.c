/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:51:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 16:42:44 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	create_threads(t_program *pg, t_philo **ps)
{
	__u_int	i;
	int		ret;

	i = 0;
	while (i < pg->n_philos)
	{
		ret = pthread_create(&ps[i]->thread, NULL, philo_thread, (void *)ps[i]);
		if (ret != 0)
			return (ft_putendl_fd(PTHREAD_CREATE_ERROR, STDERR_FILENO), false);
		i++;
	}
	ret = pthread_create(&pg->monitor, NULL, monitor_thread, (void *)pg);
	if (ret != 0)
		return (ft_putendl_fd(PTHREAD_CREATE_ERROR, STDERR_FILENO), false);
	return (true);
}

static void	join_threads(t_program *pg, t_philo **ps)
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

	philos = program->philos;
	if (!create_threads(program, philos))
		return ;
	if (set_program_ready(program) == -1)
		return ;
	return (join_threads(program, philos));
}
