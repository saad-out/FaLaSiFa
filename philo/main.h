/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 22:23:44 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/* MACROS */
# ifndef LOCK
#  define LOCK 0
# endif /* LOCK */

# ifndef UNLOCK
#  define UNLOCK 1
# endif /* UNLOCK */

# ifndef MALLOC_ERROR
#  define MALLOC_ERROR "malloc() error"
# endif /* MALLOC_ERROR */

# ifndef MUTEX_INIT_ERROR
#  define MUTEX_INIT_ERROR "pthread_mutex_init() error"
# endif /* MUTEX_INIT_ERROR */

# ifndef MUTEX_DESTROY_ERROR
#  define MUTEX_DESTROY_ERROR "pthread_mutex_destroy() error"
# endif /* MUTEX_DESTROY_ERROR */

# ifndef MUTEX_LOCK_ERROR
#  define MUTEX_LOCK_ERROR "pthread_mutex_lock() error"
# endif /* MUTEX_LOCK_ERROR */

# ifndef MUTEX_UNLOCK_ERROR
#  define MUTEX_UNLOCK_ERROR "pthread_mutex_unlock() error"
# endif /* MUTEX_UNLOCK_ERROR */

# ifndef PTHREAD_CREATE_ERROR
#  define PTHREAD_CREATE_ERROR "pthread_create() error"
# endif /* PTHREAD_CREATE_ERROR */

# ifndef PTHREAD_JOIN_ERROR
#  define PTHREAD_JOIN_ERROR "pthread_join() error"
# endif /* PTHREAD_JOIN_ERROR */

# ifndef RED
#  define RED "\x1B[31m"
# endif /* RED */

# ifndef GRN
#  define GRN "\x1B[32m"
# endif /* GRN */

# ifndef YEL
#  define YEL "\x1B[33m"
# endif /* YEL */

# ifndef BLU
#  define BLU "\x1B[34m"
# endif /* BLU */

# ifndef MAG
#  define MAG "\x1B[35m"
# endif /* MAG */

# ifndef CYN
#  define CYN "\x1B[36m"
# endif /* CYN */

# ifndef WHT
#  define WHT "\x1B[37m"
# endif /* WHT */

# ifndef RESET
#  define RESET "\x1B[0m"
# endif /* RESET */
/* ----- */

/* INCLUDES */
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>
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
	bool			finished;
	char			*color;
	__u_int			last_meal;
	t_program		*program;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex;
};

struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
};

struct s_program
{
	__u_int			n_philos;
	__u_int			t_die;
	__u_int			t_eat;
	__u_int			t_sleep;
	long			max_meals;
	bool			ready;
	bool			philo_died;
	bool			err;
	long			finished;
	t_philo			**philos;
	t_fork			**forks;
	pthread_t		monitor;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
};
/* ------ */

/* PROTOTYPES */
t_program	*parse_input(int ac, char **av);
__u_int		ft_atoerr(const char *nptr, bool *err);
t_fork		**init_forks(__u_int n);
t_philo		**init_philos(t_program *program, t_fork **forks);
void		clear_forks(t_fork	**forks, __u_int i);
void		clear_philos(t_philo **philos, __u_int i);
int			check_program_ready(t_program *program);
int			set_program_ready(t_program *program);
void		*philo_thread(void *arg);
void		start_threads(t_program *p);
__u_int		get_time(void);
int			set_program_finished(t_program *program);
long		check_program_finished(t_program *program);
int			set_program_philo_died(t_program *program);
int			check_program_philo_died(t_program *program);
bool		wait_threads(t_program *program);

bool		think(t_philo *philo, t_program *program);
bool		sleep_p(t_philo *philo, t_program *program);
bool		eat(t_philo *philo, t_program *program);
// int			ft_usleep(useconds_t time);
bool		get_forks(t_philo *philo, t_program *program);
bool		put_forks(t_philo *philo, t_program *program);
int			set_philo_last_meal(t_philo *philo);
void		*monitor_thread(void *arg);
int			set_philo_finished(t_philo *philo);
int			check_philo_finished(t_philo *philo);
bool		get_first_fork(t_philo *philo, t_program *program);
bool		get_second_fork(t_philo *philo, t_program *program);

int			safe_mutex(pthread_mutex_t *mutex, int action, t_program *program);
int			check_program_error(t_program *program);
void		set_program_error(t_program *program);
__u_int		start_time(bool init);

void		ft_putendl_fd(char const *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_usleep(__u_int time);

void		print_eating(t_philo *philo);
void		print_dead(t_philo *philo);
void		print_fork(t_philo *philo);
void		print_thinking(t_philo *philo);
void		print_sleeping(t_philo *philo);

void		philosophers(int ac, char **av);
/* --------- */

#endif /* MAIN_H */
