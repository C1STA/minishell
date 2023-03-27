/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:14:48 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/26 17:25:32 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>
#include <mcheck.h>
#include <string.h>

static size_t	lenght_of_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s && s[i] && i < start)
		i++;
	j = 0;
	while (s && s[i] && j < len)
	{
		i++;
		j++;
	}
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*p;
	size_t		i;
	size_t		max_index;
	size_t		real_size;

	i = 0;
	real_size = lenght_of_substr(s, start, len);
	p = malloc(sizeof(char) * real_size + 1);
	if (!s)
		return (NULL);
	if (p == NULL)
	{
		return (NULL);
	}
	max_index = ft_strlen(s) - 1;
	while ((i < len) && (start <= max_index) && (s[start + i] != '\0'))
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return ((p));
}
/*int main(void)
{
char * s
    	s  = ft_substr("tripouille", 0, 42000);
    printf("%p",ft_substr(NULL, 0, 42000));
    printf("%d",mcheck(s, strlen("tripouille") + 1));
}*/
