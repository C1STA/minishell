/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:53:04 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/08 19:56:00 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}
/*int main(void)
{
	char s[] = "je suis un test";
	char t[] = "je suis un test";

	bzero(s, sizeof(char)*2);
	ft_bzero(t, sizeof(char)*2);

	printf("mine is =>%s \n", t);
	printf("the real one is =>%s", s);
	
//	int x[] = {1,2,3};
//	int y[] = {1,2,3};
//	bzero(y, sizeof(int)*2);
//	ft_bzero(x, sizeof(int)*2);

//	int i = 0;
//	printf("mine is => ");
//	while (i < 3)
//	{
//		printf("%d", x[i]);
//		i++;
//	}
//	printf("\n");
//	i = 0;
//	printf("the real one is => ");
//	while (i < 3)
//	{
//		printf("%d", y[i]);
//		i++;
//	}
}*/
