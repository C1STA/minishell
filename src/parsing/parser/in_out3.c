/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:20:27 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/07 19:27:24 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	in_file_next(t_node *ptr)
{
	if (ptr -> next -> next)
	{
		if (ft_stcmp(ptr -> next -> next -> txt, "<") == 1 \
			|| ft_stcmp(ptr -> next -> next -> txt, ">") == 1)
			return (print_error_next(ptr), 0);
	}
	return (1);
}
