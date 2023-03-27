/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_mini.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:39:10 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/27 22:39:12 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putnbr_hex_mini(unsigned int nbr)
{
	unsigned int	nb;
	char			*base;
	int				i;

	nb = nbr;
	base = "0123456789abcdef";
	if ((nb < 16))
	{
		write(1, &base[nb], 1);
	}
	else if ((nb >= 16))
	{
		ft_putnbr_hex_mini(nb / 16);
		ft_putnbr_hex_mini(nb % 16);
	}
	i = count_hex_spe(nbr);
	return (i);
}
