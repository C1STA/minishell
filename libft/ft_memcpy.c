/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:15:02 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/08 19:57:19 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	char str1[] = "je suis un test";
	char str2[17];
	int test1[3] = {1,2,3};
	int test2[3];

	//ft_memcpy(str2, str1, sizeof(str1));
	//printf("%s", str2);
	ft_memcpy(test2, test1, sizeof(int)*2);
	
	int i = 0;
	while (i < 2)
	{
		printf("%d", test2[i]);
		i++;
	}	
}*/
