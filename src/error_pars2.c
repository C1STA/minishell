/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:33:14 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:33:15 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	end_comm(char *str, int i, int single, int double_q)
{
	if (str[i] == '|')
	{
		if (single % 2 != 0 || double_q % 2 != 0)
			return (print_error_quotes("quotes"), 0);
	}
	return (1);
}
