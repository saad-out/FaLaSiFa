/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/02 22:43:04 by soutchak         ###   ########.fr       */
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
# include <signal.h>
# include "libft.h"
/* ------- */

/* MARCOS */
# ifndef PROGRAM_SEM_NAME
#  define PROGRAM_SEM_NAME "forks"
# endif /* PROGRAM_SEM_NAME */

# ifndef PHILO_SEM_NAME
#  define PHILO_SEM_NAME "philos"
# endif /* PHILO_SEM_NAME */
/* ----- */

/* TYPEDEFS */
typedef struct s_program	t_program;
typedef struct s_philo		t_philo;
/* ------- */

/* STRUCTS */
struct s_philo
{
	int				id;
	bool			finished;
	bool			died;
	__u_int			last_meal;
	t_program		*program;
	sem_t			*sem;
	pid_t			pid;
	char			*name;
};

struct s_program
{
	__u_int			n_philos;
	__u_int			t_die;
	__u_int			t_eat;
	__u_int			t_sleep;
	sem_t			*sem;
	long			max_meals;
	bool			ready;
	bool			philo_died;
	long			finished;
	t_philo			**philos;
};
/* ------ */

/* PROTOTYPES */
t_program	*parse_input(int ac, char **av);
__u_int		ft_atoerr(const char *nptr, bool *err);
void		start_processes(t_program *program);
int			ft_usleep(__u_int time);
t_philo		**init_philos(t_program *program);
__u_int		get_time(void);
void		monitor(t_program *program);
void		clear_philos(t_philo **philos, __u_int i, bool parent);

void*	monitor_thread(void *arg);
void*	philo_thread(void *arg);

void	eat(t_philo *philo, t_program *program);
void	think(t_philo *philo, t_program *program);
void	sleep_p(t_philo *philo, t_program *program);
void	put_forks(t_philo *philo, t_program *program);
void	get_forks(t_philo *philo, t_program *program);

int		set_philo_last_meal(t_philo *philo);
__u_int	get_philo_last_meal(t_philo *philo);
int		set_philo_finished(t_philo *philo);
int		check_philo_finished(t_philo *philo);
int		set_philo_died(t_philo *philo);
int		check_philo_died(t_philo *philo);
/* --------- */

#endif /* MAIN_H */
