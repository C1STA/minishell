/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:31:15 by imrane            #+#    #+#             */
/*   Updated: 2023/04/15 15:37:59 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_com	**create_ast_command_redir(t_node *root)
{
	t_com	**ast;
	t_ast	*save_ast;
	t_node	*ptr;
	int		nbr_pipe;

	save_ast = NULL;
	ast = NULL;
	if (!root)
		return (NULL);
	ptr = root -> first_child;
	nbr_pipe = how_much_pipe(root);
	ast = malloc_ast(ast, nbr_pipe);
	ast = create_while(ast, save_ast, ptr, nbr_pipe);
	return (ast);
}

t_ast	*isolate_command_redir(t_node *pt)
{
	t_redir	*redir;
	t_com	*com;

	if (!pt)
		return (NULL);
	com = NULL;
	redir = NULL;
	if (pt)
	{
		while (pt && ft_stcmp(pt -> txt, "|") != 1)
		{
			while (pt && ft_stcmp(pt -> txt, "|") != 1 \
				&& ft_stcmp(pt->txt, "<") != 1 && ft_stcmp(pt->txt, ">") != 1)
			{
				com = create_com_node(com, pt);
				pt = pt -> next;
			}
			if (pt)
			{
				if (ft_stcmp(pt->txt, "<") == 1 || ft_stcmp(pt->txt, ">") == 1)
					pt = return_ptr(&redir, pt);
			}
		}
	}
	return (return_save_ast(pt, com, redir));
}

void	print_final_ast(t_com **ast)
{
	int	i;

	i = 0;
	while (ast[i])
	{
		ft_printf("------------------------\n");
		printf("command %i is :\n", i);
		print_command(ast[i]);
		print_redir(ast[i]->redir);
		ft_printf("------------------------\n");
		i++;
	}
}

void	print_command(t_com *com)
{
	t_com	*ptr;

	if (!com)
	{
		printf("there is nos command\n");
		return ;
	}
	ptr = com;
	while (ptr)
	{
		ft_printf("command is \n");
		ft_printf("%s\n", ptr -> txt);
		ptr = ptr -> next;
	}
}

void	print_redir(t_redir *redir)
{
	t_redir	*ptr;

	if (!redir)
	{
		ft_printf("there is no redir for this command\n");
		return ;
	}
	ptr = redir;
	while (ptr)
	{
		ft_printf("redir is \n");
		ft_printf("%s\n", ptr -> txt);
		ptr = ptr -> next;
	}
}
