/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:29:58 by wacista           #+#    #+#             */
/*   Updated: 2025/01/13 20:21:59 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stcmp_unset(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (0);
	if (!str2)
		return (0);
	if (str1[0] == '\0')
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_unset(t_env **head, t_node *root)
{
	t_node	*ptr;
	int		nbr;

	if (!root)
		return (1);
	nbr = how_much_pipe(root);
	if (nbr)
		return (0);
	ptr = root->first_child;
	if (ptr)
	{
		if (!ft_strcmp(ptr->txt, "unset") && ptr->next)
		{
			nbr = 1;
			ptr = ptr->next;
			while (ptr)
			{
				if (check_if_exist(*head, ptr->txt) == 1)
					supp_env(head, ptr->txt);
				ptr = ptr->next;
			}
		}
	}
	return (nbr);
}

int	check_if_exist(t_env *head, char *str)
{
	t_env	*ptr;

	if (!head)
		return (2);
	ptr = head;
	while (ptr != NULL)
	{
		if (ft_stcmp_unset(str, ptr -> var_name) == 1)
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
