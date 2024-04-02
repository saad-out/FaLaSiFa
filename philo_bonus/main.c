/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:46:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 21:11:13 by soutchak         ###   ########.fr       */
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
	sem = sem_open(PROGRAM_SEM_NAME, O_CREAT | O_EXCL, O_RDWR, program->n_philos);
	if (sem == SEM_FAILED)
		return (printf("error creating semaphor\n"),free(program), exit(EXIT_FAILURE));
	if (sem_getvalue(sem, &value) == -1)
		return (printf("error getting semaphor\n"),free(program), exit(EXIT_FAILURE));
	printf("sem value is %d\n", value);
	program->sem = sem;
	
	/* create philos */
	philos = init_philos(program);
	if (!philos)
		return (printf("error creating philos\n"),free(program), exit(EXIT_FAILURE));
	program->philos = philos;
	program->finished = 0;

	/* core */
	start_processes(program);

	/* cleanup */
	if (sem_close(sem) == -1)
		return (printf("error closing semaphor\n"),free(program), exit(EXIT_FAILURE));
	if (sem_unlink(PROGRAM_SEM_NAME) == -1)
		return (printf("error unlinking semaphor\n"),free(program), exit(EXIT_FAILURE));
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
