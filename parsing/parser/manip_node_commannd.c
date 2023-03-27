/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_node_commannd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:18:31 by imrane            #+#    #+#             */
/*   Updated: 2023/03/18 21:40:35 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_com *create_com_node(t_com *com, t_node *node)
{
	t_com *ptr;
	t_com *follow;
	ptr = malloc(sizeof(t_com));
	if (!node)
		return (NULL);
	if (!com)
	{
		
		ptr -> txt = malloc(sizeof(char)* ((ft_strlen(node -> txt) + 1)));
		ft_strlcpy(ptr -> txt, node -> txt, ft_strlen(node -> txt) + 1);
		ptr -> next_sibling = NULL;
		com = ptr;
	}
	else
	{
		follow = com;
		while (follow -> next_sibling != NULL)
			follow = follow -> next_sibling;
		follow -> next_sibling = ptr;
		ptr -> txt = malloc(sizeof(char)* ((ft_strlen(node -> txt) + 1)));
		ft_strlcpy(ptr -> txt, node -> txt, ft_strlen(node -> txt) + 1);
		ptr -> next_sibling = NULL;
	}
	return (com);
}