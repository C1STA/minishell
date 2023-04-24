/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:00:36 by wcista            #+#    #+#             */
/*   Updated: 2023/04/24 22:47:13 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	init_forks(t_final *cmds, char *env[], t_pipex *p)
{
	p->i = 0;
	p->child = (pid_t *)malloc(sizeof(pid_t) * p->nb_cmds);
	if (!p->child)
		return (print_perror("malloc"), free_pipex(p), false);
	ft_signal(4);
	while (p->i < p->nb_cmds)
	{
		p->child[p->i] = fork();
		if (p->child[p->i] == -1)
			return (fork_error(p));
		if (p->child[p->i] == 0)
		{
			ft_signal(2);
			child_processs(cmds, env, p);
		}
		p->i++;
	}
	return (true);
}

bool	init_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	p->fd = (int **)malloc(sizeof(int *) * (p->nb_cmds - 1));
	if (!p->fd)
		return (print_perror("malloc"), free(p), false);
	while (i < p->nb_cmds - 1)
	{
		p->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->fd[i])
			return (print_perror("malloc"), free_pipex(p), false);
		if (pipe(p->fd[i]) == -1)
			return (pipe_error(p, i - 1));
		i++;
	}
	return (true);
}
