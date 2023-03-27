/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:33:57 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/22 22:56:46 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <bsd/string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	save;

	i = 0;
	j = 0;
	if (ft_strlen(little) == 0)
		return ((char *)(big));
	while (((big[i] != '\0') && (little[j] != '\0')) && (i < len))
	{
		save = i;
		while (big[i] == little[j] && (i < len))
		{
			i++;
			j++;
			if (j == ft_strlen(little))
				return ((char *)(&(big[i - j])));
		}
		j = 0;
		i = save + 1;
	}
	return (NULL);
}

/*
int	main(void)
{
	char haystack[30] = "aaabcabcd";
	char needle[10] = "cd";
	
	printf("mine is =>%s\n", ft_strnstr(haystack, needle, 8));
	printf("the real one is =>%s", strnstr(haystack, needle, 8));
}*/