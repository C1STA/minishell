/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:01:23 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 19:19:45 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_comm(char *str, int i, int single, int double_q)
{
	if (str[i] == '|')
	{
		if (single % 2 != 0 || double_q % 2 != 0)
		{
			ft_printf("error : quotes are not closed\n");
			return (0);
		}
	}
	return (1);
}
