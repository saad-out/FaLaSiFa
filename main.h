/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:37:58 by soutchak          #+#    #+#             */
/*   Updated: 2024/02/27 19:24:31 by soutchak         ###   ########.fr       */
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
__u_int	ft_atoerr(const char *nptr, bool *err);
/* --------- */

#endif /* MAIN_H */
