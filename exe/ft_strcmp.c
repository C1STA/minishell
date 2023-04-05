/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:16:57 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 19:34:20 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}
