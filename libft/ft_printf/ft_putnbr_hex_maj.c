/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_maj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:39:43 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/27 22:39:45 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putnbr_hex_maj(unsigned int nbr)
{
	unsigned int	nb;
	char			*base;
	int				i;

	nb = nbr;
	base = "0123456789ABCDEF";
	if ((nb < 16))
	{
		write(1, &base[nb], 1);
	}
	else if ((nb >= 16))
	{
		ft_putnbr_hex_maj(nb / 16);
		ft_putnbr_hex_maj(nb % 16);
	}
	i = count_hex_spe(nbr);
	return (i);
}
