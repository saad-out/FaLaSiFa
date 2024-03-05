/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:58:42 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/04 22:54:40 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	eat(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	if (!philo)
		return ;
	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	end = program->err || program->philo_died;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	if (end)
	{
		printf("%d going to exit\n", philo->id);
		pthread_exit(NULL);
	}
	if (set_philo_last_meal(philo) == -1)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		return (pthread_exit(NULL));
	}
	printf("%u %d is eating\n", get_time(), philo->id);
	usleep(program->t_eat * 1000);
}

void	sleep_p(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	if (!philo)
		return ;
	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	end = program->err || program->philo_died;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	if (end)
	{
		printf("%d going to exit\n", philo->id);
		pthread_exit(NULL);
	}
	printf("%u %d is sleeping\n", get_time(), philo->id);
	usleep(program->t_sleep * 1000);
}

void	think(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	if (!philo)
		return ;
	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	end = program->err || program->philo_died;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	if (end)
	{
		printf("%d going to exit\n", philo->id);
		pthread_exit(NULL);
	}
	printf("%u %d is thinking\n", get_time(), philo->id);
}

void	get_first_fork(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	ret = pthread_mutex_lock(&philo->first_fork->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
	{
		pthread_mutex_unlock(&philo->first_fork->mutex);
		return (program->err = true, pthread_exit(NULL));
	}
	end = program->err || program->philo_died;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
	{
		pthread_mutex_unlock(&philo->first_fork->mutex);
		return (program->err = true, pthread_exit(NULL));
	}
	if (end)
	{
		pthread_mutex_unlock(&program->mutex);
		pthread_exit(NULL);
	}
	// printf("PHILO %d has first fork %d\n", philo->id, philo->first_fork->id);
	printf("%u %d has taken a fork\n", get_time(), philo->id);
}

void	get_second_fork(t_philo *philo, t_program *program)
{
	int		ret;
	bool	end;

	ret = pthread_mutex_lock(&philo->second_fork->mutex);
	if (ret != 0)
		return (program->err = true, pthread_exit(NULL));
	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
	{
		pthread_mutex_unlock(&philo->second_fork->mutex);
		return (program->err = true, pthread_exit(NULL));
	}
	end = program->err || program->philo_died;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
	{
		pthread_mutex_unlock(&philo->second_fork->mutex);
		return (program->err = true, pthread_exit(NULL));
	}
	if (end)
	{
		pthread_mutex_unlock(&program->mutex);
		pthread_exit(NULL);
	}
	// printf("PHILO %d has second fork %d\n", philo->id, philo->second_fork->id);
	printf("%u %d has taken a fork\n", get_time(), philo->id);
}

void	get_forks(t_philo *philo, t_program *program)
{
	get_first_fork(philo, program);
	get_second_fork(philo, program);
}

void	put_forks(t_philo *philo, t_program *program)
{
	int	ret;

	ret = pthread_mutex_unlock(&philo->first_fork->mutex);
	if (ret != 0)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		return (pthread_exit(NULL));
	}
	// printf("PHILO %d PUT first fork %d\n", philo->id, philo->first_fork->id);
	ret = pthread_mutex_unlock(&philo->second_fork->mutex);
	if (ret != 0)
	{
		pthread_mutex_lock(&program->mutex);
		program->err = true;
		pthread_mutex_unlock(&program->mutex);
		return (pthread_exit(NULL));
	}
	// printf("PHILO %d PUT second fork %d\n", philo->id, philo->second_fork->id);
}
