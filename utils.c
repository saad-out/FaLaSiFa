/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:04:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/29 21:26:35 by soutchak         ###   ########.fr       */
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

	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (-1);
	program->philo_died = true;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (-1);
	return (0);
}

int	check_program_philo_died(t_program *program)
{
	int		ret;
	bool	died;

	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (-1);
	died = program->philo_died;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (-1);
	return ((int)died);
}

long	check_program_finished(t_program *program)
{
	int		ret;
	long	finished;

	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (-1);
	finished = program->finished;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (-1);
	return (finished);
}

int	set_program_finished(t_program *program)
{
	int	ret;

	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (-1);
	program->finished++;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (-1);
	return (0);
}

int	check_program_ready(t_program *program)
{
	int		ret;
	bool	ready;

	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (-1);
	ready = program->ready;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
		return (-1);
	return ((int)ready);
}

int	set_program_ready(t_program *program)
{
	int	ret;

	ret = pthread_mutex_lock(&program->mutex);
	if (ret != 0)
		return (-1);
	program->ready = true;
	ret = pthread_mutex_unlock(&program->mutex);
	if (ret != 0)
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
