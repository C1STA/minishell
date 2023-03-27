/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:42:13 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/05 15:42:18 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	int		lenght;
	int		i;

	i = 0;
	lenght = ft_strlen(s);
	p = malloc(sizeof(char) * (lenght + 1));
	if (p == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(p, s, lenght + 1);
	while (s[i] != '\0')
	{
		p[i] = f(i, p[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
