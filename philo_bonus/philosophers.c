/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:55:05 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 09:50:39 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_philo		**philos;
	sem_t		*sem;

	/* parsing */
	program = parse_input(ac, av);
	if (!program)
		return (printf("wrong input\n"), exit(EXIT_FAILURE));
	sem_unlink(PROGRAM_SEM_NAME);
	sem_unlink(PRINT_LOCK);
	sem_unlink(FORKS);
	
	/* create semaphore (forks) */
	sem = sem_open(PROGRAM_SEM_NAME, O_CREAT, 0777, 1);
	if (sem == SEM_FAILED)
		return (perror("error creating semaphor1\n"),free(program), exit(EXIT_FAILURE)); // maybe close the prog semaphore
	program->var_lock = sem;
	sem = sem_open(FORKS, O_CREAT | O_EXCL, 0777, program->n_philos);
	if (sem == SEM_FAILED)
		return (printf("error creating semaphor\n"),free(program), exit(EXIT_FAILURE));
	program->forks = sem;
	sem = sem_open(PRINT_LOCK, O_CREAT | O_EXCL, 0777, 1);
	if (sem == SEM_FAILED)
		return (printf("error creating semaphor\n"),free(program), exit(EXIT_FAILURE)); // maybe close the prog semaphore
	program->print_lock = sem;
	
	/* create philos */
	philos = init_philos(program);
	if (!philos)
		return (printf("error creating philos\n"),free(program), exit(EXIT_FAILURE));
	program->philos = philos;
	program->finished = 0;
	program->error = false;

	/* core */
	start_processes(program);

	/* cleanup */
	if (sem_close(program->var_lock) == -1)
		printf("error closing semaphor\n");
	if (sem_close(program->print_lock) == -1)
		printf("error closing semaphor\n");
	if (sem_close(program->forks) == -1)
		printf("error closing semaphor\n");
	clear_philos(philos, program->n_philos, true);
	free(program);
}
