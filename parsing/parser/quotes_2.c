/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:05:39 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/23 02:46:32 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exit_status;

int	single_quote_closed(t_node *head)
{
	t_node	*ptr;
	int		count;

	count = 0;
	if (!head)
		return (2);
	ptr = head -> first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr -> txt, "'") == 1)
			count++;
		ptr = ptr -> next;
	}
	if (count % 2 != 0)
		return (print_error_quotes("single quotes"), 0);
	return (1);
}

int	double_quote_closed(t_node *head)
{
	t_node	*ptr;
	int		count;

	count = 0;
	if (!head)
		return (2);
	ptr = head -> first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr -> txt, "\"") == 1)
			count++;
		ptr = ptr -> next;
	}
	if (count % 2 != 0)
		return (print_error_quotes("double quotes"), 0);
	return (1);
}

int	quote_closed(t_node *head)
{
	if (single_quote_closed(head) == 0)
		return (0);
	if (double_quote_closed(head) == 0)
		return (0);
	return (1);
}
