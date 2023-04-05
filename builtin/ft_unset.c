/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:06:55 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/02 17:24:42 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void     is_unset(t_env **head, t_node *root)
{
	t_node *ptr;
	int nbr;
	if (!root)
		return ;
	nbr =  how_much_pipe(root);
	if (nbr != 0)
		return ;
	ptr = root -> first_child;
	if (ptr)
	{
		if (ft_stcmp(ptr -> txt, "unset") && (ptr -> next_sibling != NULL))
		{
			if(check_if_exist(*head, ptr -> next_sibling -> txt ) == 1)
				supp_env(head, ptr -> next_sibling -> txt);
		}
		ptr = ptr -> next_sibling;
	}
}

int check_if_exist(t_env *head, char *str)
{
	t_env *ptr;
	
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

void supp_env(t_env **head, char *str)
{
	t_env *ptr;
	t_env *before;
	
	if (!head)
		return ;
		
	ptr = *head;
	if (!ptr)
		return ;
	// si premier
	if (ft_stcmp(str, ptr -> var_name) == 1)
	{
		free(ptr -> var_name);
		free(ptr -> var_value);
		free(ptr -> txt);
		*head = ptr -> next;
		free(ptr);
		return ;
	}
	// si au milieu
	before = ptr;
	while (ptr -> next != NULL)
	{
		if (ft_stcmp(str, ptr -> var_name) == 1)
		{
			
			free(ptr -> var_name);
			free(ptr -> var_value);
			free(ptr -> txt);
			before -> next =  ptr -> next;
			free (ptr);
			return ;
		}
		before = ptr;
		ptr = ptr -> next;
	}
	// si dernier

	if (ft_stcmp(str, ptr -> var_name) == 1)
	{
		free(ptr -> var_name);
		free(ptr -> var_value);
		free(ptr -> txt);
		before -> next = NULL;
		free(ptr);
		return ;
	}
}