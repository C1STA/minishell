/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:11:01 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/07 00:11:04 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long long	nbr;
	char		c;

	nbr = n;
	if (n < 0)
	{
		nbr = nbr * -1;
		write(fd, "-", 1);
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
}
