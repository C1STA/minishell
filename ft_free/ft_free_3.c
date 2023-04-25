/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:41:13 by wcista            #+#    #+#             */
/*   Updated: 2023/04/25 15:48:33 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_ast_loop(t_final *ast, t_final *save_ast, \
t_redir *save_redir, int i)
{
	while (ast)
	{
		save_ast = ast -> next;
		while (ast -> cmds[i])
		{
			free(ast -> cmds[i]);
			ast -> cmds[i] = NULL;
			i++;
		}
		free(ast -> cmds);
		while (ast -> redir)
		{
			save_redir = ast -> redir -> next;
			if (ast -> redir -> txt)
				free(ast -> redir -> txt);
			ast -> redir -> txt = NULL;
			if (ast -> redir)
				free(ast -> redir);
			ast -> redir = NULL;
			ast -> redir = save_redir;
		}
		i = 0;
		free(ast);
		ast = save_ast;
	}
}

void	ft_free_final_ast(t_final **ast_before)
{
	t_final	*ast;
	t_final	*save_ast;
	t_redir	*save_redir;
	int		i;

	if (!ast_before)
		return ;
	ast = *ast_before;
	if (!ast)
		return ;
	i = 0;
	save_ast = NULL;
	save_redir = NULL;
	ft_free_ast_loop(ast, save_ast, save_redir, i);
	ast_before = NULL;
}
