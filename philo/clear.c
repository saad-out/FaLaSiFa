/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:25:40 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/08 19:03:59 by soutchak         ###   ########.fr       */
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

void	clear_forks(t_fork	**forks, __u_int i)
{
	__u_int	j;

	if (!forks)
		return ;
	j = 0;
	while (j < i)
		free(forks[j++]);
	free(forks);
}
