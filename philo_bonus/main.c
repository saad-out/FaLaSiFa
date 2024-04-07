/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:46:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/04/06 10:59:48 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_putendl_fd("wrong input", STDERR_FILENO), EXIT_FAILURE);
	philosophers(ac - 1, av + 1);
	return (0);
}
