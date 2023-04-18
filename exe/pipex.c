/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:47:53 by wcista            #+#    #+#             */
 /*   Updated: 2023/04/17 17:48:18 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

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
		i++;
	}
}

void	lonely_exit(t_pipex *p, int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	g_exit_status = p->exit_status;
	free_pipex(p);
}

void	lonely_builtin(t_final *cmds, char *env[], t_pipex *p)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!init_redir(cmds->redir, p))
		lonely_exit(p, saved_stdin, saved_stdout);
	if (!ft_strcmp(cmds->cmds[0], "exit"))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	builtin_exe(cmds, env, p);
	lonely_exit(p, saved_stdin, saved_stdout);
}

void	pipex(t_final *cmds, char *env[])
{
	t_pipex	*p;

	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		return (print_perror("malloc"));
	p->nb_cmds = lenlist(cmds);
	p->child = NULL;
	p->fd = NULL;
	p->i = 0;
	p->exit_status = cmds->exit_tmp;
	if (p->nb_cmds == 1 && isbuiltin(cmds))
		return (lonely_builtin(cmds, env, p));
	if (!init_pipes(p))
		return ;
	if (!init_forks(cmds, env, p))
		return ;
	close_pipes_main(p);
	wait_childs(p);
	free_pipex(p);
}
