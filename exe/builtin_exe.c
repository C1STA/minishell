/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:50:34 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 02:12:38 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	builtin_exe_exit(t_final *cmds, t_pipex *p, int i)
{
	close(p->fd[i][0]);
	close(p->fd[i + 1][1]);
	exit(EXIT_SUCCESS);
}

void	builtin_exe_echo(t_final *cmds, t_pipex *p, int i)
{
	t_redir	*redir;

	while (redir)
	{
		
	}
}

void	builtin_exe(t_final *cmds, t_pipex *p, int i)
{
	if ((!ft_strcmp(cmds->cmds[0], "export")) && cmds->cmds[1] == NULL)
		// PRINT ENV A -> Z --> check redirections (export sans options)
	if((!ft_strcmp(cmds->cmds[0], "export")) && cmds->cmds[1] != NULL)
		// EXIT AVEC LES BONS PIPES (pass) (export avec options)
	if (!ft_strcmp(cmds->cmds[0], "unset"))
		// EXIT AVEC LES BONS PIPES (pass)
	if (!ft_strcmp(cmds->cmds[0], "env"))
		//print env --> check redirections
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		builtin_exe_exit(cmds, p, i);
	if (!ft_strcmp(cmds->cmds[0], "echo"))
		
}

bool	ft_builtin_check(t_final *cmds, t_pipex *p, int i)
{
	int	j;

	j = 0;
	while (cmds)
	{
		if (i == j)
			builtins_exe(cmds, p, i);
		cmds = cmds->next_sibling;
		j++;
	}
}
