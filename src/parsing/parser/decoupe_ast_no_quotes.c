/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:31:15 by imrane            #+#    #+#             */
/*   Updated: 2024/11/22 15:30:10 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	**create_ast_command_redir(t_node *root)
{
	t_com	**ast;
	t_node	*ptr;
	int		nbr_pipe;

	ast = NULL;
	ptr = NULL;
	nbr_pipe = 0;
	if (!root)
		return (NULL);
	ptr = root->first_child;
	nbr_pipe = how_much_pipe(root);
	ast = malloc_ast(nbr_pipe);
	ast = create_while(ast, ptr, nbr_pipe);
	return (ast);
}

void	isolate_command_redir(t_node **pt, t_com **com, t_redir **redir)
{
	if (!pt || !*pt)
		return ;
	*com = NULL;
	if (*pt)
	{
		while (*pt && ft_stcmp((*pt)->txt, "|") != 1)
		{
			while (*pt && ft_stcmp((*pt)->txt, "|") != 1 \
				&& ft_stcmp((*pt)->txt, "<") != 1 && ft_stcmp((*pt)->txt, ">") != 1)
			{
				*com = create_com_node(*com, *pt);
				*pt = (*pt)->next;
			}
			if (*pt)
			{
				if (ft_stcmp((*pt)->txt, "<") == 1 || ft_stcmp((*pt)->txt, ">") == 1)
					*pt = return_ptr(redir, *pt);
			}
		}
		*pt = (*pt)->next;
	}
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
