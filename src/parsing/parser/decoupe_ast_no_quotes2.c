/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:07:06 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/22 15:30:19 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	**malloc_ast(int nbr_pipe)
{
	t_com **ast_mall;

	if (nbr_pipe > 0)
	{
		ast_mall = malloc(sizeof(t_com *) * ((nbr_pipe + 1) + 1));
		ast_mall[(nbr_pipe + 1)] = NULL;
	}
	else
	{
		ast_mall = malloc(sizeof(t_com *) * 2);
		ast_mall[1] = NULL;
		nbr_pipe = 0;
	}
	return (ast_mall);
}

void	printnode(t_node *ptr)
{
	while (ptr)
	{
		printf("**%s**\n", ptr->txt);
		ptr = ptr->next;
	}
}

t_com	**create_while(t_com **ast, t_node *ptr, int nbr_pipe)
{
	int		i;
	t_com	*com;
	t_redir	*redir;

	i = 0;
	com = NULL;
	redir = NULL;
	while (nbr_pipe-- >= 0)
	{
		isolate_command_redir(&ptr, &com, &redir);
		if (ptr)
		{
			if (com)
			{
				ast[i] = com;
			}
			else
			{
				ast[i] = malloc(sizeof(t_com));
				ast[i]->txt = NULL;
			}
			if (ast[i])
			{
				if (redir)
					ast[i]->redir = redir;
				else
					ast[i]->redir = NULL;
			}
			i++;
		}
	}
	return (ast);
}

t_node	*return_ptr(t_redir **redir, t_node *pt)
{
	if ((pt->next && ft_stcmp(pt->next->txt, "<") == 1) || (pt->next
			&& (ft_stcmp(pt->next->txt, ">") == 1)))
	{
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			pt = pt->next;
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			pt = pt->next;
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
	}
	else if (pt && ft_stcmp(pt->txt, "|") != 1)
	{
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
		if (pt)
			pt = pt->next;
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
	}
	if (pt && ft_stcmp(pt->txt, "|") != 1)
		pt = pt->next;
	return (pt);
}

t_ast	*return_save_ast(t_node *ptr, t_com *com, t_redir *redir)
{
	t_ast	*save_ast;

	if (ptr)
		ptr = ptr->next;
	save_ast = (t_ast *)malloc(sizeof(t_ast));
	if (com)
		save_ast->command = com;
	else
		save_ast->command = NULL;
	if (redir)
		save_ast->redir = redir;
	else
		save_ast->redir = NULL;
	if (ptr)
		save_ast->save_ptr = ptr;
	return (save_ast);
}
