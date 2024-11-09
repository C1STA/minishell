/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:45:52 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/07 19:27:24 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	after_multiple_dollar_while(int nbr, int *i, int *save)
{
	if (nbr % 2 == 0)
	{
		while (nbr)
		{
			*(i) = *(i) + 1;
			nbr--;
		}
		*(save) = *(i);
	}
	else
	{
		while (nbr > 1)
		{
			*(i) = *(i) + 1;
			nbr--;
		}
		*(save) = *(i);
	}
}

void	init_str_nbr(char *str_nbr)
{
	str_nbr[0] = '3';
	str_nbr[1] = '1';
	str_nbr[2] = '0';
	str_nbr[3] = '5';
	str_nbr[4] = '1';
	str_nbr[5] = '6';
	str_nbr[6] = '0';
	str_nbr[7] = '\0';
}

int	expand_guillemets(char *str, int index_dol)
{
	int	i;
	int	save_index_dol;
	int	index_simple;
	int	nbr_double_q;
	int	nbr_simple;

	i = 0;
	nbr_simple = 0;
	nbr_double_q = 0;
	save_index_dol = index_dol;
	expand_guillemets_first(str, &index_dol, &nbr_simple, &index_simple);
	if (nbr_simple == 0)
		return (1);
	index_dol = save_index_dol;
	while (i <= index_simple)
	{
		if (str[i] == '"')
			nbr_double_q++;
		i++;
	}
	if (nbr_simple % 2 == 0)
		return (1);
	if (nbr_double_q > 0 && nbr_double_q % 2 != 0)
		return (1);
	return (0);
}

t_node	*attribue_here_doc(t_node *root)
{
	t_node	*ptr;

	if (!root)
		return (NULL);
	ptr = root -> first_child;
	if (ptr)
		ptr -> quotes = 0;
	while (ptr)
	{
		if (is_it_heredoc(ptr) == 1)
		{
			ptr -> heredoc = 0;
			ptr -> next -> heredoc = 1;
			return (ptr -> next);
		}
		else
		{
			ptr -> heredoc = 0;
			ptr -> after_here_doc = 0;
		}
		ptr = ptr -> next;
	}
	return (NULL);
}

void	attribute_atfer_here_doc(t_node *node)
{
	t_node	*ptr;

	if (!node)
		return ;
	ptr = node -> next;
	while (ptr)
	{
		if (does_str_has_quotes(ptr->txt) == 1)
			ptr -> quotes = 1;
		else
			ptr -> quotes = 0;
		ptr -> after_here_doc = 1;
		ptr = ptr -> next;
	}
}
