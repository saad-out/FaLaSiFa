/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 11:17:20 by soutchak         ###   ########.fr       */
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
#include <sys/types.h>
# include "libft.h"
/* ------- */

/* MARCOS */
# ifndef PROGRAM_SEM_NAME
#  define PROGRAM_SEM_NAME "program2"
# endif /* PROGRAM_SEM_NAME */

# ifndef FORKS
#  define FORKS "forks2"
# endif /* FORKS */

# ifndef PRINT_LOCK
#  define PRINT_LOCK "printf2"
# endif /* PRINT_LOCK */

# ifndef PHILO_SEM_NAME
#  define PHILO_SEM_NAME "philos2"
# endif /* PHILO_SEM_NAME */

# ifndef POST
#  define POST 1
# endif /* POST */

# ifndef WAIT
#  define WAIT 0
# endif /* WAIT */

# ifndef THINK_TIME
#  define THINK_TIME 1
# endif /* THINK_TIME */

# ifndef SEM_OPEN_ERROR
#  define SEM_OPEN_ERROR "error creating semaphore"
# endif /* SEM_OPEN_ERROR */

# ifndef SEM_CLOSE_ERROR
#  define SEM_CLOSE_ERROR "error closing semaphor"
# endif /* SEM_CLOSE_ERROR */

# ifndef SEM_UNLINK_ERROR
#  define SEM_UNLINK_ERROR "error unlinking semaphore"
# endif /* SEM_UNLINK_ERROR */

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "malloc() error"
# endif /* MALLOC_ERROR */

# ifndef P_CREATE_ERROR
#  define P_CREATE_ERROR "pthread_create() error"
# endif /* PTHREAD_CREATE_ERROR */

# ifndef P_JOIN_ERROR
#  define P_JOIN_ERROR "pthread_join() error"
# endif /* PTHREAD_JOIN_ERROR */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
/* ----- */

/* TYPEDEFS */
typedef struct s_program	t_program;
typedef struct s_philo		t_philo;
/* ------- */

typedef unsigned int	__u_int;

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
	char			*color;
};

struct s_program
{
	__u_int			n_philos;
	__u_int			t_die;
	__u_int			t_eat;
	__u_int			t_sleep;
	sem_t			*forks;
	sem_t			*var_lock;
	sem_t			*print_lock;
	long			max_meals;
	bool			philo_died;
	bool			error;
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
void		philosophers(int ac, char **av);

void*	monitor_thread(void *arg);
void*	philo_thread(void *arg);

bool	eat(t_philo *philo, t_program *program);
bool	think(t_philo *philo, t_program *program);
bool	sleep_p(t_philo *philo, t_program *program);
bool	put_forks(t_philo *philo, t_program *program);
bool	get_forks(t_philo *philo, t_program *program);

int		set_philo_last_meal(t_philo *philo);
__u_int	get_philo_last_meal(t_philo *philo);
int		set_philo_finished(t_philo *philo);
int		check_philo_finished(t_philo *philo);
int		set_philo_died(t_philo *philo);
int		check_philo_died(t_philo *philo);
__u_int	get_time_since_last_meal(t_philo *philo, bool *err);
int		set_program_philo_died(t_program *program);
int		check_program_philo_died(t_program *program);

int		safe_sem(sem_t *sem, int action, t_program *program);
void	set_program_error(t_program *program);
int		check_program_error(t_program *program);

void	kill_all_except(t_philo **philos, __u_int n, pid_t exception);

void	close_program_semaphores(t_program *program);
/* --------- */

#endif /* MAIN_H */
