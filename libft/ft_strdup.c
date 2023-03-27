/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:59:57 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/22 17:29:13 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*p;
	int		lenght;

	i = 0;
	lenght = ft_strlen(s);
	p = malloc(sizeof(char) * lenght + 1);
	if (p == NULL)
	{
		return (NULL);
	}
	while (s[i] != '\0')
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*int	main(void)
{
	const char c[] = "je suis une star";
	printf("%s", ft_strdup(c));
}*/
