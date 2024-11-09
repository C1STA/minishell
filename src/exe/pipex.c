/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:59:17 by wcista            #+#    #+#             */
/*   Updated: 2024/11/07 19:26:04 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	close_unused_pipes(t_pipex *p)
{
	int	j;

	j = 0;
	while (j < p->nb_cmds - 1)
	{
		if (p->i != j)
			close(p->fd[j][1]);
		if (p->i - 1 != j)
			close(p->fd[j][0]);
		j++;
	}
}

static void	close_pipes_main(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
}

static void	wait_childs(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds)
	{
		waitpid(p->child[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = (WEXITSTATUS(g_exit_status));
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		i++;
	}
	ft_signal(1);
}

void	pipex(t_final *cmds, char *env[], t_main *m)
{
	t_pipex	*p;

	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		return (print_perror("malloc"));
	p->i = 0;
	p->fd = NULL;
	p->child = NULL;
	p->nb_cmds = lenlist(cmds);
	p->exit_status = cmds->exit_tmp;
	if (p->nb_cmds == 1 && isbuiltin(cmds))
		return (lonely_builtin(cmds, env, p, m));
	if (!init_pipes(p))
		return ;
	if (!init_forks(cmds, env, p, m))
		return ;
	close_pipes_main(p);
	wait_childs(p);
	free_pipex(p);
}
