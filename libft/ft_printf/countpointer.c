/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countpointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:23:49 by imoumini          #+#    #+#             */
/*   Updated: 2022/11/19 16:49:42 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	countpointer(unsigned long long int n)
{
	int						power;
	unsigned long long int	nbr;

	power = 0;
	nbr = n;
	if ((n < 16) && (n > 0))
	{
		return (1);
	}
	while (nbr >= 16)
	{
		nbr = nbr / 16;
		power++;
	}
	return (power + 1);
}
