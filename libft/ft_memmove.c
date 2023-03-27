/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:20:40 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/13 20:52:46 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src > dst)
	{
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n)
		{
			n--;
			((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
		}
	}
	return (dst);
}

/*int	main(void)
{
	char str1[50] = "1234";
	
	ft_memmove(&str1[2],str1, sizeof(char)*2);
	printf("%s", str1);
}*/
