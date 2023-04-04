/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:00:36 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 05:26:13 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	init_forks(t_final *cmds, t_pipex *p, t_env *env)
{
	int	i;

	i = 0;
	p->child = (pid_t *)malloc(sizeof(pid_t) * p->len + 1);
	if (!p->child)
		return (free_pipex(p), false);
	while (i < p->len)
	{
		p->child[i] = fork();
		if (p->child[i] == -1)
			return (fork_error(p));
		if (p->child[i] == 0)
			child_processs(cmds, p, i, env);
		i++;
	}
	return (true);
}

bool	init_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	p->fd = (int **)malloc(sizeof(int *) * p->len + 1);
	if (!p->fd)
		return (false);
	while (i < p->len + 1)
	{
		p->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->fd[i])
			return (free_pipex(p), false);
		if (pipe(p->fd[i]) == -1)
			return (pipe_error(p, i));
		i++;
	}
	return (true);
}
