/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:32:22 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/30 23:32:24 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_put_pointer(unsigned long long int nbr)
{
	unsigned long long int	nb;
	char					*base;
	int						i;

	nb = nbr;
	base = "0123456789abcdef";
	if ((nb < 16))
	{
		write(1, &base[nb], 1);
	}
	else if ((nb >= 16))
	{
		ft_put_pointer(nb / 16);
		ft_put_pointer(nb % 16);
	}
	i = countpointer(nbr);
	return (i);
}
