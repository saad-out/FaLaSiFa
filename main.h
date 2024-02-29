/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/29 21:34:40 by soutchak         ###   ########.fr       */
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
	long			finished;
	t_philo			**philos;
	t_fork			**forks;
	pthread_t		monitor;
	pthread_mutex_t	mutex;
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
// void		start_threads(t_program *, t_philo **, t_fork **);
void		start_threads(t_program *);
__u_int		get_time(void);
int			set_program_finished(t_program *program);
long		check_program_finished(t_program *program);
int			set_program_philo_died(t_program *program);
int			check_program_philo_died(t_program *program);
/* --------- */

#endif /* MAIN_H */
