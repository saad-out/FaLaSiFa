/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:57:45 by soutchak          #+#    #+#             */
/*   Updated: 2024/05/09 22:54:18 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

__u_int	ft_atoerr(const char *nptr, bool *err)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	*err = 0;
	while (ft_isspace(nptr[i]))
		i++;
	while (nptr[i] == '+')
		i++;
	if (nptr[i] == '-' || !nptr[i])
		return (*err = 1, 0);
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > UINT_MAX)
			return (*err = 1, 0);
		i++;
	}
	if (nptr[i] != '\0')
		return (*err = 1, 0);
	return ((__u_int)(result));
}

int	ft_usleep(__u_int time)
{
	__u_int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(60);
	return (0);
}

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
