/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:01:23 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/18 02:35:33 by wcista           ###   ########.fr       */
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
