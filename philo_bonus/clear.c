/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:55:21 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 10:56:21 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	clear_philos(t_philo **philos, __u_int i, bool parent)
{
	__u_int	j;

	if (!philos)
		return ;
	j = 0;
	while (j < i)
	{
		if (sem_close(philos[j]->sem) == -1)
			ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
		if (parent && sem_unlink(philos[j]->name) == -1)
			ft_putendl_fd(SEM_UNLINK_ERROR, STDERR_FILENO);
		free(philos[j]->name);
		free(philos[j]);
		j++;
	}
	free(philos);
}
