/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:53:48 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/19 19:46:29 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;

	if (nmemb && ((nmemb * size / nmemb) != size))
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	i = 0;
	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		((char *)p)[i] = '\0';
		i++;
	}
	return (p);
}

/*int	main(void)
{
	char *a;
	char *b;
	int	i = 0;

	printf("mine is \n");
	a = ft_calloc(3, 1);
	while (i <= 3)
	{
		printf("%c", a[i]);
		i++;
	}
	i = 0;
	printf("the real one is \n");
	b = calloc(3, 1);
        while (i <= 3)
        {
                printf("%c", b[i]);
		i++;
        }

}*/
