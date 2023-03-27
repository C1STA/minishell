/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:37:42 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/27 22:37:45 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	unsigned long long int	nbr;
	char					c;
	int						i;

	nbr = n;
	i = count_int_spe(nbr);
	if (nbr < 10)
	{
		c = nbr + '0';
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_unsigned_fd(nbr / 10, fd);
		ft_putnbr_unsigned_fd(nbr % 10, fd);
	}
	return (i);
}
