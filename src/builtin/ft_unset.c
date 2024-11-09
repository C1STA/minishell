/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:06:55 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/07 19:25:02 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_unset(t_env **head, t_node *root)
{
	t_node	*ptr;
	int		nbr;

	if (!root)
		return ;
	nbr = how_much_pipe(root);
	if (nbr != 0)
		return ;
	ptr = root -> first_child;
	if (ptr)
	{
		if (ft_stcmp(ptr -> txt, "unset") && (ptr -> next != NULL))
		{
			if (check_if_exist(*head, ptr -> next -> txt) == 1)
				supp_env(head, ptr -> next -> txt);
		}
		ptr = ptr -> next;
	}
}

int	check_if_exist(t_env *head, char *str)
{
	t_env	*ptr;

	if (!head)
		return (2);
	ptr = head;
	while (ptr != NULL)
	{
		if (ft_stcmp(str, ptr -> var_name) == 1)
			return (1);
		ptr = ptr -> next;
	}
	return (0);
}

void	supp_env(t_env **head, char *str)
{
	t_env	*ptr;
	t_env	*before;

	if (!head)
		return ;
	ptr = *head;
	if (!ptr)
		return ;
	if (supp_env_first(ptr, head, str) == 1)
		return ;
	before = ptr;
	while (ptr -> next != NULL)
	{
		if (supp_env_milieu(ptr, before, str) == 1)
			return ;
		before = ptr;
		ptr = ptr -> next;
	}
	if (supp_env_last(ptr, str, before) == 1)
		return ;
}
