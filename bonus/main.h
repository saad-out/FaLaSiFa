/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/03/01 22:43:50 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/* INCLUDES */
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
/* ------- */

/* TYPEDEFS */
typedef struct s_program	t_program;
typedef struct s_fork		t_fork;
typedef struct s_philo		t_philo;
/* ------- */

/* STRUCTS */
struct s_philo
{
	int				id;
	__u_int			last_meal;
	t_program		*program;
	pid_t			pid;
	// t_fork			*first_fork;
	// t_fork			*second_fork;
	// pthread_t		thread;
	// pthread_mutex_t	mutex;
};

// struct s_fork
// {
// 	int				id;
// 	pthread_mutex_t	mutex;
// };

struct s_program
{
	__u_int			n_philos;
	__u_int			t_die;
	__u_int			t_eat;
	__u_int			t_sleep;
	long			max_meals;
	bool			ready;
	bool			philo_died;
	long			finished;
	t_philo			**philos;
	// t_fork			**forks;
	// pthread_t		monitor;
	// pthread_mutex_t	mutex;
};
/* ------ */

/* PROTOTYPES */
t_program	*parse_input(int ac, char **av);
__u_int		ft_atoerr(const char *nptr, bool *err);
void		start_processes(t_program *program, sem_t *sem);
/* --------- */

#endif /* MAIN_H */
