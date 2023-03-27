/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:56:16 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/08 19:58:28 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) || (c >= 48 && c <= 57))
	{
		return (1);
	}
	return (0);
}
/*int	main(void)
{
	int a = '9';
	int b = 'a';
	int c = '+';
	printf("%i \n", ft_isalnum(a));
	printf("%i \n", ft_isalnum(b));
	printf("%i \n", ft_isalnum(c));
}*/
