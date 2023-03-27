/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:18:23 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/22 17:18:30 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*t;

	i = 0;
	t = s;
	while (i < n)
	{
		if (t[i] == (unsigned char)c)
		{
			return ((char unsigned *)s + i);
		}
		i++;
	}
	return (NULL);
}
/*int	main(void)
{
	char s[] = "de rien je suis frais";
	int c = 'r';

	printf("%p", ft_memchr(s, c,21));

	
}*/
