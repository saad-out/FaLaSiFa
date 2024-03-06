/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:18:28 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/07 00:29:57 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	philo_dead(t_program *program)
{
	int		i;
	int		ret;
	bool	died;
	__u_int	time;

	i = 0;
	died = false;
	while (i < program->n_philos && !died)
	{
		if (program->philos[i]->finished)
		{
			i++;
			continue ;
		}
		time = get_time();
		if (program->philos[i]->last_meal < time - program->t_die)
		{
			printf("%u %d died\n", time, program->philos[i]->id);
			printf("philo %d died:\n\tlast meal: %u\n\ttime: %u\n", program->philos[i]->id, program->philos[i]->last_meal, time);
			printf("\tpassed: %u\n", time - program->philos[i]->last_meal);
			died = true;
		}
		i++;
	}
	return (died);
}

void	monitor(t_program *program)
{
	int		end;
	__u_int	i;

	usleep(5 * 1000);
	end = 0;
	while (!end)
	{
		if (philo_dead(program))
		{
			printf("END OF SIMULATION...PHILO DIED\n");
			end = 1;
		}
		else if (program->finished >= program->n_philos)
		{
			printf("END OF SIMULATION...GOOD\n");
			end = -1;
		}
		if (!end)
			usleep(8 * 1000);
	}
	if (end == 1)
	{
		printf("lets kill=====================\n");
		// kill all process
		i = 0;
		while (i < program->n_philos)
			kill(program->philos[i++]->pid, SIGINT);
	}
}
