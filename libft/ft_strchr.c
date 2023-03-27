/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 21:18:00 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/19 21:40:55 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(s);
	while (s[i] != '\0')
	{
		if (s[i] == (const char)c)
		{
			return (&((char *)s)[i]);
		}
		i++;
	}
	if ((const char)c == '\0')
	{
		return (&((char *)s)[l]);
	}
	return (NULL);
}
/*int     main(void)
{
	//int  c = 106;
	//char d;
	//d = c;
	char s[] = "je suis bg\n";
        printf("%s", ft_strchr(s, 106));
	//printf("%c", d);
}*/
