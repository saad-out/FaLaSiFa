/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/09 15:05:27 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

__u_int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL); //TODO: handle error
	return ((__u_int)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	set_program_philo_died(t_program *program)
{
	int	ret;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	program->philo_died = true;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	check_program_philo_died(t_program *program)
{
	int		ret;
	bool	died;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	died = program->philo_died;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return ((int)died);
}

long	check_program_finished(t_program *program)
{
	int		ret;
	long	finished;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	finished = program->finished;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (finished);
}

int	set_program_finished(t_program *program)
{
	int	ret;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	program->finished++;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	check_program_ready(t_program *program)
{
	int		ret;
	bool	ready;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	ready = program->ready;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return ((int)ready);
}

int	set_program_ready(t_program *program)
{
	int	ret;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	program->ready = true;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
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
		usleep(60);
	return (0);
}

int	set_philo_last_meal(t_philo *philo)
{
	int	ret;

	ret = safe_mutex(&philo->mutex, LOCK, philo->program);
	if (ret == -1)
		return (-1);
	philo->last_meal = get_time();
	ret = safe_mutex(&philo->mutex, UNLOCK, philo->program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	set_philo_finished(t_philo *philo)
{
	int	ret;

	ret = safe_mutex(&philo->mutex, LOCK, philo->program);
	if (ret == -1)
		return (-1);
	philo->finished = true;
	ret = safe_mutex(&philo->mutex, UNLOCK, philo->program);
	if (ret == -1)
		return (-1);
	return (0);
}

int	check_philo_finished(t_philo *philo)
{
	int	ret;
	bool	finished;

	ret = safe_mutex(&philo->mutex, LOCK, philo->program);
	if (ret == -1)
		return (-1);
	finished = philo->finished;
	ret = safe_mutex(&philo->mutex, UNLOCK, philo->program);
	if (ret == -1)
		return (-1);
	return ((int)finished);
}
