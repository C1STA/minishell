/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:53:30 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/22 17:42:21 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s);
	while (l >= 0)
	{
		if (s[l] == (const char)c)
		{
			return (&((char *)s)[l]);
		}
		l--;
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
	char s[] = "je suis jbg";
        printf("%s", ft_strrchr(s, 106));
	//printf("%c", d);
}*/
