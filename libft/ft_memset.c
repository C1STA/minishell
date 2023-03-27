/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:21:20 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/08 19:55:20 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*int	main(void)
{
	int str1[5] = {1,2,3,4,5};
	int str2[5] = {1,2,3,4,5};
	int i = 0;
	size_t n = sizeof(int)*4;

	char str3[] = "je suis un test";
	char str4[] = "je suis un test";
	ft_memset(str1, 0, n);
	memset(str2, 0,  n);
	printf("my function => ");
	while (i < 5)
	{
		printf("%i", str1[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("the real one => ");
	while (i < 5)
	{
		printf("%d", str2[i]);
		i++;
	}
	//ft_memset(str3, 97, n);
        //memset(str4, 97,  n);
	//printf("my function => %s \n", str3);
	//printf("the real one => %s", str4);

}*/
