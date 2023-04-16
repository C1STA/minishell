/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_node_redir3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:14:40 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 18:49:37 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_outfile(t_redir *ptr)
{
	ptr -> out_file = 1;
}

void	add_new_redir_to_list(t_redir *redir, t_redir *ptr, t_node *node)
{
	t_redir	*follow;

	follow = redir;
	while (follow -> next != NULL)
		follow = follow -> next;
	follow -> next = ptr;
	ptr -> txt = malloc(sizeof(char) * ((ft_strlen(node -> txt) + 1)));
	ft_strlcpy(ptr -> txt, node -> txt, ft_strlen(node -> txt) + 1);
	ptr -> next = NULL;
}

t_redir	*create_redir_node_if(t_redir *redir, t_node *node, t_redir *ptr)
{
	if (ft_stcmp(node -> txt, "<") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, "<") == 1)
		return (ft_heredoc_redir(ptr), redir);
	if (ft_stcmp(node -> txt, "<") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, "<") != 1)
		return (ft_file(ptr), redir);
	if (ft_stcmp(node -> txt, ">") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, ">") == 1)
		return (ft_append(ptr), redir);
	if (ft_stcmp(node -> txt, ">") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, ">") != 1)
		return (ft_outfile(ptr), redir);
	ptr -> file = 1;
	return (redir);
}

t_redir	*create_redir_node_else(t_redir *redir, t_node *node, t_redir *ptr)
{
	if (ft_stcmp(node -> txt, "<") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, "<") == 1)
		return (ft_heredoc_redir(ptr), redir);
	if (ft_stcmp(node -> txt, "<") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, "<") != 1)
		return (ft_file(ptr), redir);
	if (ft_stcmp(node -> txt, ">") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, ">") == 1)
		return (ft_append(ptr), redir);
	if (ft_stcmp(node -> txt, ">") == 1 && node -> next \
		&& ft_stcmp(node -> next -> txt, ">") != 1)
		return (ft_outfile(ptr), redir);
	ptr -> file = 1;
	return (redir);
}
