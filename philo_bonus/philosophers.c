/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:55:05 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 10:59:56 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	close_program_semaphores(t_program *program)
{
	if (sem_close(program->var_lock) == -1)
		ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
	if (sem_close(program->print_lock) == -1)
		ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
	if (sem_close(program->forks) == -1)
		ft_putendl_fd(SEM_CLOSE_ERROR, STDERR_FILENO);
}

static void	open_semaphores(t_program *program)
{
	sem_t	*sem;

	sem = sem_open(PROGRAM_SEM_NAME, O_CREAT | O_EXCL, 0777, 1);
	if (sem == SEM_FAILED)
	{
		ft_putendl_fd(SEM_OPEN_ERROR, STDERR_FILENO);
		return (free(program), exit(EXIT_FAILURE));
	}
	program->var_lock = sem;
	sem = sem_open(FORKS, O_CREAT | O_EXCL, 0777, program->n_philos);
	if (sem == SEM_FAILED)
	{
		ft_putendl_fd(SEM_OPEN_ERROR, STDERR_FILENO);
		sem_close(program->var_lock);
		return (free(program), exit(EXIT_FAILURE));
	}
	program->forks = sem;
	sem = sem_open(PRINT_LOCK, O_CREAT | O_EXCL, 0777, 1);
	if (sem == SEM_FAILED)
	{
		ft_putendl_fd(SEM_OPEN_ERROR, STDERR_FILENO);
		sem_close(program->var_lock);
		return (sem_close(program->forks), free(program), exit(EXIT_FAILURE));
	}
	program->print_lock = sem;
}

static void	unlink_semaphores(void)
{
	sem_unlink(PROGRAM_SEM_NAME);
	sem_unlink(PRINT_LOCK);
	sem_unlink(FORKS);
}

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_philo		**philos;

	program = parse_input(ac, av);
	if (!program)
		return (printf("wrong input"), exit(EXIT_FAILURE));
	unlink_semaphores();
	open_semaphores(program);
	philos = init_philos(program);
	if (!philos)
	{
		ft_putendl_fd("error creating philos", STDERR_FILENO);
		close_program_semaphores(program);
		return (free(program), exit(EXIT_FAILURE));
	}
	program->philos = philos;
	program->finished = 0;
	program->philo_died = false;
	program->error = false;
	start_processes(program);
	close_program_semaphores(program);
	clear_philos(philos, program->n_philos, true);
	free(program);
}
