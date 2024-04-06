/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 23:39:02 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	create_threads(t_philo *philo, pthread_t *pt, pthread_t *mt)
{
	int	ret;

	ret = pthread_create(pt, NULL, philo_thread, (void *)philo);
	if (ret != 0)
	{
		ft_putendl_fd(P_CREATE_ERROR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ret = pthread_create(mt, NULL, monitor_thread, (void *)philo);
	if (ret != 0)
	{
		ft_putendl_fd(P_CREATE_ERROR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	join_threads(pthread_t pt, pthread_t mt, void *ret_value)
{
	int	ret;

	ret = pthread_join(mt, &ret_value);
	if (ret != 0)
	{
		ft_putendl_fd(P_JOIN_ERROR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ret = pthread_join(pt, NULL);
	if (ret != 0)
	{
		ft_putendl_fd(P_JOIN_ERROR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	start_threads(t_philo *philo)
{
	t_program	*program;
	pthread_t	monitor_t;
	pthread_t	philo_t;
	int			ret;
	void		*ret_value;

	program = philo->program;
	ret_value = NULL;
	create_threads(philo, &philo_t, &monitor_t);
	join_threads(philo_t, monitor_t, ret_value);
	clear_philos(philo->program->philos, philo->program->n_philos, false);
	if (sem_close(program->var_lock) == -1)
		ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
	if (sem_close(program->print_lock) == -1)
		ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
	if (sem_close(program->forks) == -1)
		ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
	free(program);
	ret = *(int *)ret_value;
	free(ret_value);
	exit(ret);
}

static bool	spawn_processes(t_program *program, t_philo **philos)
{
	__u_int	i;
	pid_t	pid;

	i = 0;
	while (i < program->n_philos)
	{
		pid = fork();
		if (pid == -1)
			return (ft_putendl_fd("fork() error", STDERR_FILENO), false);
		else if (pid == 0)
		{
			start_threads(program->philos[i]);
			ft_putendl_fd("start_threads should not return", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		else
			philos[i]->pid = pid;
		i++;
	}
	return (true);
}

void	start_processes(t_program *program)
{
	pid_t	pid;
	t_philo	**philos;
	int		status;
	__u_int	i;

	philos = program->philos;
	if (!spawn_processes(program, philos))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < program->n_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
		{
			ft_putendl_fd("waitpid() error", STDERR_FILENO);
			kill_all_except(philos, program->n_philos, 0);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
			continue ;
		else
			return (kill_all_except(philos, program->n_philos, pid));
		i++;
	}
}
