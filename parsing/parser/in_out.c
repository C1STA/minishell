/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:17:23 by imrane            #+#    #+#             */
/*   Updated: 2023/03/10 20:14:12 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int in_file_second_check(t_node *ptr)
{
	if (!ptr)
		return (1);
	if ((ptr -> next_sibling) == NULL) // si ya un seul < et ya rien après le <
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (ptr) // si ya un seul < ou un seul >
	{
		if (ft_stcmp(ptr -> txt, "<") == 1)
		{
			if (ptr -> next_sibling) // si ya un truc après le <
			{
				if (ft_stcmp(ptr -> next_sibling -> txt, ">") == 1)
					{
						ft_printf("syntax error near unexpected token '%s'\n", ptr -> next_sibling -> txt);
						return (0);
					}
			}
		}
		if (ft_stcmp(ptr -> txt, ">") == 1)
		{
			if (ptr -> next_sibling) // si ya un truc après le <
			{
				if (ft_stcmp(ptr -> next_sibling -> txt, "<") == 1)
					{
						ft_printf("syntax error near unexpected token '%s'\n", ptr -> next_sibling -> txt);
						return (0);
					}
			}
		}
	}
	return (1);
}
int ft_in_file_first_check(t_node *ptr)
{
	if (!ptr)
		return (1);
	if (ptr -> next_sibling)
	{
		if (ft_stcmp(ptr -> txt, "<") == 1 && ft_stcmp(ptr -> next_sibling -> txt, ">") == 1)
		{
			ft_printf("syntax error near unexpected token '>'\n");
			return (0);
		}
		if (ft_stcmp(ptr -> txt, ">") == 1 && ft_stcmp(ptr -> next_sibling -> txt, "<") == 1)
		{
			ft_printf("syntax error near unexpected token '<'\n");
			return (0);
		}
		// si ya  << ou >>
		// si ya >>
		// si ya <<
		if (ft_stcmp(ptr -> next_sibling -> txt, "<") == 1 || ft_stcmp(ptr -> next_sibling -> txt, ">") == 1)
		{
			if (ptr -> next_sibling -> next_sibling == NULL)
			{
				ft_printf("syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (ptr -> next_sibling -> next_sibling)
			{
				if (ft_stcmp(ptr -> next_sibling -> next_sibling -> txt, "<") == 1 || ft_stcmp(ptr -> next_sibling -> next_sibling -> txt, ">") == 1)
				{
					ft_printf("syntax error near unexpected token '%s'\n", ptr -> next_sibling -> next_sibling -> txt);
					return (0);
				}
			}
		}
	}
	return (1);
}
int ft_in_file(t_node *head)
{
    t_node *ptr;
    
	ptr = head;
    if (!ptr)
		return(2);
	if (ptr -> first_child)
		ptr = ptr -> first_child;
	while (ptr != NULL)
	{
		if (ft_stcmp(ptr -> txt, "<") == 1 || ft_stcmp(ptr -> txt, ">") == 1 )
		{
			if (ft_in_file_first_check(ptr) == 0)
				return (0);
			if (in_file_second_check(ptr) == 0)
				return (0);
			// avancer juste qua être un truc différent de < ou >
			while (ptr && (ft_stcmp(ptr -> txt, "<") == 1 || ft_stcmp(ptr -> txt, ">") == 1))
				ptr = ptr -> next_sibling;
		}
		if (ptr && ft_stcmp(ptr -> txt, "<") != 1 && ft_stcmp(ptr -> txt, ">") != 1)
			ptr = ptr -> next_sibling;	
	}
	
	return (1);
    
}

int is_here_doc(t_node *root)
{
	t_node *ptr;
	
	if (!root)
		return (2);
	ptr = root -> first_child;
	while (ptr)
	{	
		if (ft_stcmp(ptr -> txt, "<"))
		{
			if (ptr -> next_sibling)
			{
				if (ft_stcmp(ptr -> next_sibling -> txt, "<"))
					return (1);
			}
		}
		ptr = ptr ->next_sibling;
	}
	return (0);
}