/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:35 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 22:29:30 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

__u_int	start_time(bool init)
{
	static __u_int	start = 0;

	if (init)
		start = get_time();
	return (start);
}

__u_int	get_time(void)
{
	struct timeval	time;
	__u_int			start;

	start = start_time(false);
	gettimeofday(&time, NULL);
	return ((__u_int)(time.tv_sec * 1000 + time.tv_usec / 1000) - start);
}

int	ft_usleep(__u_int time)
{
	__u_int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(60);
	return (0);
}
