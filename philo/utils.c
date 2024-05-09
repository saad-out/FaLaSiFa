/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:35 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 18:46:11 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

__u_int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((__u_int)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

int	ft_usleep(__u_int time)
{
	__u_int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(60);
	return (0);
}
