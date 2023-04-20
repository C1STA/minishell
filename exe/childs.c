/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:57:37 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 13:43:03 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

static t_final	*get_right_cmd(t_final *cmds, int i)
{
	int	j;

	j = 0;
	while (cmds)
	{
		if (j == i)
			return (cmds);
		cmds = cmds->next;
		j++;
	}
	return (cmds);
}

void	child_processs(t_final *cmds, char *env[], t_pipex *p)
{
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;

	close_unused_pipes(p);
	tmp_cmds = get_right_cmd(cmds, p->i);
	tmp_redir = tmp_cmds->redir;
	if (p->i != 0)
		dup2(p->fd[p->i - 1][0], STDIN_FILENO);
	if (p->i != p->nb_cmds - 1)
		dup2(p->fd[p->i][1], STDOUT_FILENO);
	if (!init_redir(tmp_redir, p))
		exit_exe(cmds, env, p);
	if (!builtin(tmp_cmds, env, p))
	{
		if (tmp_cmds->cmds[0])
			if (execve(tmp_cmds->cmds[0], tmp_cmds->cmds, env) == -1)
				print_exec(tmp_cmds->cmds[0], p);
	}
	exit_exe(cmds, env, p);
}
