/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 22:05:59 by soutchak         ###   ########.fr       */
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
	t_program		*program;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	mutex;
};

struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
};

struct s_program
{
	__u_int	n_philos;
	__u_int	t_die;
	__u_int	t_eat;
	__u_int	t_sleep;
	long	max_meals;
};
/* ------ */

/* PROTOTYPES */
t_program	*parse_input(int ac, char **av);
__u_int		ft_atoerr(const char *nptr, bool *err);
t_fork		**init_forks(__u_int n);
void		clear_forks(t_fork	**forks, __u_int i);
/* --------- */

#endif /* MAIN_H */
