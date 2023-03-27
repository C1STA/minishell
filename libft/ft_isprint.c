/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:40:52 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/08 19:52:15 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <ctype.h>
#include "libft.h"

int	ft_isprint(int c)
{
	if (!(c >= 0 && c <= 31) && (c <= 126))
	{
		return (1);
	}
	return (0);
}
/*int	main(void)
{
	int c = 127;
	printf("%i \n", ft_isprint(c));
	printf("%i", isprint(c));
}*/
