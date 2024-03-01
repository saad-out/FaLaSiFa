/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:30:37 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/01 23:10:05 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	start_processes(t_program *program, sem_t *sem)
{
	pid_t	pid;

	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = fork();
		if (pid == -1)
			return (printf("fork error\n"), (void)0);
		else if (pid == 0)
		{
			printf("child %u doing some work...\n", i);
			sleep(1);
			printf("child %u finished its work...\n", i);
			if (sem_close(sem) == -1)
				return (printf("error closing semaphor\n"),free(program), exit(EXIT_FAILURE));
			free(program);
			exit(EXIT_SUCCESS);
			// return ;
		}
	}
	for (__u_int i = 0; i < program->n_philos; i++)
	{
		pid = wait(NULL);
		printf("child terminated\n");
	}
}
