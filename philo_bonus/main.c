/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:46:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/04 23:35:05 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philosophers(int ac, char **av)
{
	t_program	*program;
	t_philo		**philos;
	sem_t		*sem;
	int			value;

	/* parsing */
	program = parse_input(ac, av);
	if (!program)
		return (printf("wrong input\n"), exit(EXIT_FAILURE));
	
	/* create semaphore (forks) */
	sem = sem_open(PROGRAM_SEM_NAME, O_CREAT | O_EXCL, O_RDWR, 1);
	if (sem == SEM_FAILED)
		return (printf("error creating semaphor\n"),free(program), exit(EXIT_FAILURE)); // maybe close the prog semaphore
	program->var_lock = sem;
	sem = sem_open(FORKS, O_CREAT | O_EXCL, O_RDWR, program->n_philos);
	if (sem == SEM_FAILED)
		return (printf("error creating semaphor\n"),free(program), exit(EXIT_FAILURE));
	program->forks = sem;
	sem = sem_open(PRINT_LOCK, O_CREAT | O_EXCL, O_RDWR, 1);
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
	if (sem_unlink(PROGRAM_SEM_NAME) == -1)
		printf("error unlinking semaphor\n");
	if (sem_close(program->print_lock) == -1)
		printf("error closing semaphor\n");
	if (sem_unlink(PRINT_LOCK) == -1)
		printf("error unlinking semaphor\n");
	if (sem_close(program->forks) == -1)
		printf("error closing semaphor\n");
	if (sem_unlink(FORKS) == -1)
		printf("error unlinking semaphor\n");
	clear_philos(philos, program->n_philos, true);
	free(program);
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("wrong input\n"), EXIT_FAILURE);
	philosophers(ac - 1, av + 1);
	return (0);
}
