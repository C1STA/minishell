/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_spe_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:36:57 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/27 22:37:00 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putnbr_spe_fd(int n, int fd)
{
	long long	nbr;
	char		c;
	int			i;

	nbr = n;
	if (n < 0)
	{
		nbr = nbr * -1;
		write(1, "-", 1);
	}
	if (nbr < 10)
	{
		c = nbr + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	i = count_int_spe(n);
	return (i);
}
