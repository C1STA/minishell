/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:20:27 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 15:49:30 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	in_file_next(t_node *ptr)
{
	if (ptr -> next -> next)
	{
		if (ft_stcmp(ptr -> next -> next -> txt, "<") == 1 \
			|| ft_stcmp(ptr -> next -> next -> txt, ">") == 1)
		{
			print_error_next(ptr);
			return (0);
		}
	}
	return (1);
}

void	print_error_next(t_node *ptr)
{
	printf("syntax error near unexpected token '%s'\n", ptr->next->next->txt);
}

void	print_error_second_check(t_node *ptr)
{
	printf("syntax error near unexpected token '%s'\n", ptr->next-> txt);
}
