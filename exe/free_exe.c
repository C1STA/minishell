/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:28:49 by wcista            #+#    #+#             */
/*   Updated: 2023/04/24 22:34:24 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	free_exe(t_final **cmds, char ***env)
{
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;
	t_redir	*redir_free;
	int		i;

	while (*cmds)
	{
		i = 0;
		tmp_cmds = (*cmds)->next;
		tmp_redir = (*cmds)->redir;
		while (tmp_redir)
		{
			redir_free = tmp_redir;
			tmp_redir = tmp_redir->next;
			ft_free_str(&redir_free->txt);
			free(redir_free);
		}
		while ((*cmds)->cmds[i])
			free((*cmds)->cmds[i++]);
		free((*cmds)->cmds);
		free(*cmds);
		*cmds = tmp_cmds;
	}
	free_final_env(env);
}

void	exit_exe(t_final *cmds, char *env[], t_pipex *p)
{
	if (p->i != p->nb_cmds - 1)
	{
		close(p->fd[p->i][1]);
		close(STDOUT_FILENO);
	}
	if (p->i != 0)
	{
		close(p->fd[p->i - 1][0]);
		close(STDIN_FILENO);
	}
	g_exit_status = p->exit_status;
	free_pipex(p);
	free_exe(&cmds, &env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_signal(5);
	exit(g_exit_status);
}
