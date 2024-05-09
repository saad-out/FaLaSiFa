/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:48:17 by saad              #+#    #+#             */
/*   Updated: 2024/05/08 18:31:19 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_program_error(t_program *program)
{
	int	ret;
	int	err;

	ret = safe_mutex(&program->mutex, LOCK, program);
	if (ret == -1)
		return (-1);
	err = (int)program->err;
	ret = safe_mutex(&program->mutex, UNLOCK, program);
	if (ret == -1)
		return (-1);
	return (err);
}

void	set_program_error(t_program *program)
{
	pthread_mutex_lock(&program->mutex);
	program->err = true;
	pthread_mutex_unlock(&program->mutex);
}

int	safe_mutex(pthread_mutex_t *mutex, int action, t_program *program)
{
	int	ret;

	ret = -1;
	if (action == LOCK)
		ret = pthread_mutex_lock(mutex);
	else if (action == UNLOCK)
		ret = pthread_mutex_unlock(mutex);
	if (ret != 0)
	{
		ft_putendl_fd("safe_mutex() error", STDERR_FILENO);
		set_program_error(program);
		return (pthread_exit(NULL), -1);
	}
	return (0);
}
