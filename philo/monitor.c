/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:52:09 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/15 01:22:42 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

//TODO: monitor should check if philo died not philo reporting it died

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
		ret = check_philo_finished(program->philos[i]);
		if (ret == -1)
		{
			pthread_mutex_lock(&program->mutex);
			program->err = true;
			pthread_mutex_unlock(&program->mutex);
			return (pthread_exit(NULL), false);
		}
		if (ret)
		{
			i++;
			continue ;
		}
		ret = pthread_mutex_lock(&program->philos[i]->mutex);
		if (ret != 0)
		{
			pthread_mutex_lock(&program->mutex);
			program->err = true;
			pthread_mutex_unlock(&program->mutex);
			return (pthread_exit(NULL), false);
		}
		time = get_time();
		if (program->philos[i]->last_meal <= time - program->t_die)
		{
			ret = set_program_philo_died(program);
			if (ret == -1)
			{
				pthread_mutex_lock(&program->mutex);
				program->err = true;
				pthread_mutex_unlock(&program->mutex);
				return (pthread_exit(NULL), false);
			}
			died = true;
			safe_mutex(&program->print_mutex, LOCK, program);
			printf("%u %d died\n", time, program->philos[i]->id);
			printf("philo %d died:\n\tlast meal: %u\n\ttime: %u\n", program->philos[i]->id, program->philos[i]->last_meal, time);
			printf("\tpassed: %u\n", time - program->philos[i]->last_meal);
			safe_mutex(&program->print_mutex, UNLOCK, program);
		}
		ret = pthread_mutex_unlock(&program->philos[i]->mutex);
		if (ret != 0)
		{
			pthread_mutex_lock(&program->mutex);
			program->err = true;
			pthread_mutex_unlock(&program->mutex);
			return (pthread_exit(NULL), false);
		}
		i++;
	}
	return (died);
}

void	*monitor_thread(void *arg)
{
	t_program	*program;
	int			ret;

	if (!arg)
		return (NULL);
	program = (t_program *)arg;
	ret = 0;
	while (!ret)
	{
		ret = check_program_ready(program);
		if (ret == -1)
			return (NULL); // TODO: stop all threads
	}
	ft_usleep(2);
	ret = 1;
	while (ret)
	{
		if (philo_dead(program))
		{
			printf("END OF SIMULATION UNSUCCESSFULLY...PHILO DIED\n");
			break ;
		}
		ret = check_program_finished(program);
		if (ret == -1)
			return (printf("mutex error\n"), NULL); // TODO: stop all threads
		if (ret == program->n_philos)
		{
			printf("END OF SIMULATION SUCCESSFULLY...\n");
			break ;
		}
		ret = 1;
		ft_usleep(8);
	}
	return (NULL);
}
