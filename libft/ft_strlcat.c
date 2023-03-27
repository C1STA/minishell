/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 21:48:17 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/13 20:48:52 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>
#include <string.h>
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	i;
	size_t	s;

	l = ft_strlen(dst);
	s = ft_strlen(src);
	i = 0;
	if (size == 0 || l >= size)
	{
		return (s + size);
	}
	while ((src[i] != '\0') && (i < size - 1 - l))
	{
		dst[l + i] = src[i];
		i++;
	}
	dst[l + i] = '\0';
	return (l + s);
}
/*int	main(void)
{
	char src1[] = "je suis un test";
	char src2[] = "je suis un test";
	//char src3[] = "je suis un test";
	char dst1[50] = "a";
	char dst2[50] = "a";
	//char dst3[50] = "je suis un test";
	
	printf("return mine is %zu\n",ft_strlcat(dst1, src1, 15));
	printf("return real is %zu\n",strlcat(dst2, src2, 15));
	//strncat(dst3, src3, 15);
	printf("mine =>%s\n", dst1);
	printf("real =>%s", dst2);
	//printf("strncat is =>%s", dst3);
}*/
