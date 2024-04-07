/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 03:02:06 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/07 03:03:12 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	ft_nbr_len(int nbr, int *sign)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		*sign = 1;
		len++;
	}
	else if (!nbr)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;
	int		sign;

	sign = 0;
	len = ft_nbr_len(nbr, &sign);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while ((!sign && len) || (sign && len > 1))
	{
		str[--len] = (nbr % 10) * (1 - 2 * sign) + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
