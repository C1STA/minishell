/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 21:04:14 by imoumini          #+#    #+#             */
/*   Updated: 2022/11/19 16:51:40 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_function_p(va_list ap)
{
	int					lenght;
	unsigned long long	p;

	lenght = 0;
	p = va_arg(ap, unsigned long long);
	if (p == 0)
	{
		lenght = lenght + (write(1, "(nil)", 5));
	}
	else
	{
		write(1, "0x", 2);
		lenght = 2 + lenght + printpointer(p);
	}
	return (lenght);
}

int	ft_function_c_and_pourcentage(va_list ap, char c)
{
	int	lenght;

	lenght = 0;
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		lenght++;
	}
	if (c == 'c')
	{
		ft_putchar_fd((char)va_arg(ap, int), 1);
		lenght++;
	}
	return (lenght);
}

int	ft_all_functions(va_list ap, char c)
{
	int	lenght;

	lenght = 0;
	if (c == '%' || c == 'c')
		lenght = lenght + ft_function_c_and_pourcentage(ap, c);
	if (c == 's')
		lenght = lenght + printstr(va_arg(ap, char *));
	if (c == 'p' )
		lenght = lenght + ft_function_p(ap);
	if (c == 'd')
		lenght = lenght + ft_putnbr_spe_fd(va_arg(ap, int), 1);
	if (c == 'i')
		lenght = lenght + ft_putnbr_spe_fd(va_arg(ap, int), 1);
	if (c == 'u')
		lenght = lenght + ft_putnbr_unsigned_fd(va_arg(ap, unsigned int), 1);
	if (c == 'x')
		lenght = lenght + ft_putnbr_hex_mini(va_arg(ap, int));
	if ((c == 'X'))
		lenght = lenght + ft_putnbr_hex_maj(va_arg(ap, int));
	return (lenght);
}

int	ft_printf(const char *stringparams, ...)
{
	va_list	ap;
	int		i;
	int		lenght;

	i = 0;
	lenght = 0;
	va_start (ap, stringparams);
	while (stringparams[i] != '\0')
	{
		if (stringparams[i] == '%')
		{
			i++;
			lenght = lenght + ft_all_functions(ap, stringparams[i]);
			i++;
		}
		else if ((stringparams[i] != '\0') && (stringparams[i] != '%'))
		{
			ft_putchar_fd(stringparams[i], 1);
			i++;
			lenght++;
		}
	}
	va_end(ap);
	return (lenght);
}
