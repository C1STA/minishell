/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:38:33 by imoumini          #+#    #+#             */
/*   Updated: 2022/05/27 15:16:53 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

static int	is_in_set(char const a, char const	*set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (a == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static int	count_real_size(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		while ((is_in_set(s1[i], set)) && (s1[i] != '\0'))
		{
			i++;
		}
		while (((is_in_set(s1[i], set) == 0)) && (s1[i] != '\0'))
		{
			i++;
			j++;
		}
		while ((is_in_set(s1[i], set))
			&& (!(is_in_set(s1[i + 1], set))) && (s1[i] != '\0'))
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	i = 0;
	p = malloc(sizeof(char) * count_real_size(s1, set) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		while ((is_in_set(s1[i], set)) && (s1[i] != '\0'))
			i++;
		while (((is_in_set(s1[i], set) == 0)) && (s1[i] != '\0'))
		{
			p[j++] = s1[i++];
		}
		while ((is_in_set(s1[i], set))
			&& (!(is_in_set(s1[i + 1], set))) && (s1[i] != '\0'))
		{
			p[j++] = s1[i++];
		}
	}
	p[j] = '\0';
	return (p);
}
/*int main(void)
{
	//printf("the final result id =>%s", ft_strtrim("xyxmathxieuyxy", "xy"));
	char	*strtrim;


		char s1[] = "lorem ipsum dolor sit amet";
		if (!(strtrim = ft_strtrim(s1, "te")))
			printf("NULL");
		else
			printf("%s",ft_strtrim(s1, "te"));
		if (ft_strtrim(s1, " ") == s1)
			printf("\nA new string was not returned");
}*/
