/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saad <saad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 02:30:57 by saad              #+#    #+#             */
/*   Updated: 2024/04/15 02:33:57 by saad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_eating(t_philo *philo)
{
	char	*color;
	int		id;

	id = philo->id;
	color = philo->color;
	printf("%s%u %d is eating%s\n", color, get_time(), id, RESET);
}

void	print_sleeping(t_philo *philo)
{
	char	*color;
	int		id;

	id = philo->id;
	color = philo->color;
	printf("%s%u %d is sleeping%s\n", color, get_time(), id, RESET);
}

void	print_thinking(t_philo *philo)
{
	char	*color;
	int		id;

	id = philo->id;
	color = philo->color;
	printf("%s%u %d is thinking%s\n", color, get_time(), id, RESET);
}

void	print_fork(t_philo *philo)
{
	char	*color;
	int		id;

	id = philo->id;
	color = philo->color;
	printf("%s%u %d has taken a fork%s\n", color, get_time(), id, RESET);
}

void	print_dead(t_philo *philo)
{
	char	*color;
	int		id;

	id = philo->id;
	color = philo->color;
	printf("%s%u %d died%s\n", color, get_time(), id, RESET);
}
