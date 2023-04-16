/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:57:53 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/14 19:00:14 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	return (0);
}
