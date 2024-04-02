/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 22:42:50 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_philo_died(t_philo *philo)
{
	int	died;

	if (sem_wait(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	died = philo->died;
	if (sem_post(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	return (died);
}

int	set_philo_died(t_philo *philo)
{
	if (sem_wait(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	philo->died = true;
	if (sem_post(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	return (0);
}

int	check_philo_finished(t_philo *philo)
{
	int	finished;

	if (sem_wait(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	finished = philo->finished;
	if (sem_post(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	return (finished);
}

int	set_philo_finished(t_philo *philo)
{
	if (sem_wait(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	philo->finished = true;
	if (sem_post(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	return (0);
}

__u_int	get_philo_last_meal(t_philo *philo)
{
	__u_int	last_meal;

	if (sem_wait(philo->sem) == -1)
		return (perror("sem wait monitor"), 0);
	last_meal = philo->last_meal;
	if (sem_post(philo->sem) == -1)
		return (perror("sem wait monitor"), 0);
	return (last_meal);
}

int	set_philo_last_meal(t_philo *philo)
{
	if (sem_wait(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	philo->last_meal = get_time();
	if (sem_post(philo->sem) == -1)
		return (perror("sem wait monitor"), -1);
	return (0);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

__u_int	ft_atoerr(const char *nptr, bool *err)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	*err = 0;
	while (ft_isspace(nptr[i]))
		i++;
	while (nptr[i] == '+')
		i++;
	if (nptr[i] == '-' || !nptr[i])
		return (*err = 1, 0);
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > UINT_MAX)
			return (*err = 1, 0);
		i++;
	}
	if (nptr[i] != '\0')
		return (*err = 1, 0);
	return ((__u_int)(result));
}

int	ft_usleep(__u_int time)
{
	__u_int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

__u_int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL); //TODO: handle error
	return ((__u_int)(time.tv_sec * 1000 + time.tv_usec / 1000));
}
