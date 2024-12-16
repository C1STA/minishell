/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:29:33 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:32:26 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_enter(char *input)
{
	if (!input)
		return (1);
	if (input[0] == '\0')
		return (1);
	if (ft_strlen(input) <= 0)
		return (1);
	if (input[0] == '\n')
		return (1);
	if (only_space(input) == 1)
		return (1);
	return (0);
}

int	only_space(char *str)
{
	int	i;
	int	letter;

	i = 0;
	letter = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			letter++;
		i++;
	}
	if (letter == 0)
		return (1);
	return (0);
}
