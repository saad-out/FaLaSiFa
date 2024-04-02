/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:12:38 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 23:14:13 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	eat(t_philo *philo, t_program *program)
{
	int	ret;

	ret = check_philo_died(philo);
	if (ret != 0)
		return ;
	printf("philo %d started eating (last meal => %u ms ago)\n", philo->id, get_time() - philo->last_meal);
	if (set_philo_last_meal(philo) == -1)
		return (perror("eat sem\n"), (void)0);
	usleep(program->t_eat * 1000);
}

void	think(t_philo *philo, t_program *program)
{
	int	ret;

	ret = check_philo_died(philo);
	if (ret != 0)
		return ;
	printf("philo %d is thinking\n", philo->id);
}

void	sleep_p(t_philo *philo, t_program *program)
{
	int	ret;

	ret = check_philo_died(philo);
	if (ret != 0)
		return ;
	printf("philo %d is sleeping\n", philo->id);
	usleep(program->t_sleep * 1000);
}

void	put_forks(t_philo *philo, t_program *program)
{
	int	ret;

	ret = check_philo_died(philo);
	if (ret != 0)
		return ;
	ret = sem_post(philo->program->sem);
	if (ret == -1)
		return (perror("sem post get fork 1"), (void)0);
	printf("philo %d put down first fork\n", philo->id);
	ret = sem_post(philo->program->sem);
	if (ret == -1)
		return (perror("sem post get fork 2"), (void)0);
	printf("philo %d put down second fork\n", philo->id);
}

void	get_forks(t_philo *philo, t_program *program)
{
	int	ret;

	ret = check_philo_died(philo);
	if (ret != 0)
		return ;
	ret = sem_wait(philo->program->sem);
	if (ret == -1)
		return (perror("sem wait get fork 1"), (void)0);
	printf("philo %d has taken first fork\n", philo->id);
	ret = sem_wait(philo->program->sem);
	if (ret == -1)
		return (perror("sem wait get fork 2"), (void)0);
	printf("philo %d has taken second fork\n", philo->id);
}
