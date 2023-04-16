/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 21:53:16 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 15:37:59 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_final	*create_final_ast(t_com **ast)
{
	t_final	*final;
	int		i;

	final = NULL;
	i = 0;
	while (ast[i])
	{
		final = create_list_final_ast(final, ast[i]);
		i++;
	}
	return (final);
}

t_final	*create_list_final_ast(t_final *final, t_com *ast)
{
	t_final	*ptr;
	t_final	*follow;

	ptr = malloc(sizeof(t_final));
	if (!ast)
		return (NULL);
	if (!final)
	{
		ptr -> cmds = break_linked_list_in_double_tab(ast);
		ptr -> redir = ast -> redir;
		ptr -> next = NULL;
		final = ptr;
	}
	else
	{
		follow = final;
		while (follow -> next != NULL)
			follow = follow -> next;
		follow -> next = ptr;
		ptr -> cmds = break_linked_list_in_double_tab(ast);
		ptr -> redir = ast -> redir;
		ptr -> next = NULL;
	}
	return (final);
}

char	**break_linked_list_in_double_tab(t_com *com)
{
	char	**tab;
	t_com	*follow;
	int		i;

	i = 0;
	if (!com)
		return (NULL);
	follow = com;
	tab = malloc(sizeof(char *) * (ft_com_len(com) + 1));
	while (follow)
	{
		if (follow -> txt)
		{
			tab[i] = malloc(sizeof(char) * (ft_strlen(follow -> txt) + 1));
			ft_strlcpy(tab[i], follow -> txt, (ft_strlen(follow -> txt) + 1));
			follow = follow -> next;
			tab[++i] = NULL;
		}
		else
		{
			tab[i] = NULL;
			follow = follow -> next;
		}
	}
	return (tab);
}

int	ft_com_len(t_com *com)
{
	t_com	*follow;
	int		i;

	i = 0;
	follow = com;
	while (follow)
	{
		i++;
		follow = follow -> next;
	}
	return (i);
}

void printf_final_ast(t_final *final)
{
	t_final *follow;
	t_redir *follow_redir;
	int i;
	int j;
	
	j = 0;
	i = 0;
	if (!final)
		return ;
	follow = final;
	while (follow)
	{
		ft_printf("---------------------------\n");
		ft_printf("for command %i :\n", j);
		ft_printf("command is : \n");
		while (follow -> cmds[i])
		{
			ft_printf("%s\n", follow -> cmds[i]);
			i++;
		}
		ft_printf("redir is : \n");
		follow_redir = follow -> redir;
		if (!follow_redir)
			ft_printf("this command as no redir\n");
		while (follow_redir)
		{
			ft_printf("%s, heredoc : %i, in_file : %i, out_file : %i, append : %i, file : %i\n", follow_redir -> txt, follow_redir -> heredoc, follow_redir -> in_file, follow_redir -> out_file, follow_redir -> append, follow_redir -> file);
			follow_redir = follow_redir -> next;
		}
		i = 0;
		j++;
		follow = follow -> next;
	}
}
