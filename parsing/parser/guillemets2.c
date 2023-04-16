/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guillemets2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:05:39 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 15:37:59 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	{
		ft_printf("error : single quote are not closed\n");
		return (0);
	}
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
	{
		ft_printf("error : double quote are not closed\n");
		return (0);
	}
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
