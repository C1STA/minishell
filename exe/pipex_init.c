/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:00:36 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 20:30:01 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	init_forks(t_final *cmds, t_pipex *p)
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
			child_processs(cmds, p, i);
		i++;
	}
	return (true);
}

void	print_pipes(t_pipex *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->fd[i])
	{
		j = 0;
		while (p->fd[j])
		{
			printf("p-fd[%d][%d]\n", i, j);
			j++;
		}
		i++;
	}
}

bool	init_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	p->fd = (int **)ft_calloc(sizeof(int *), p->len + 1);
	if (!p->fd)
		return (false);
	while (i < p->len + 1)
	{
		p->fd[i] = (int *)ft_calloc(sizeof(int), 2);
		if (!p->fd[i])
			return (free_pipex(p), false);
		if (pipe(p->fd[i]) == -1)
			return (pipe_error(p, i));
		i++;
	}
	print_pipes(p);
	return (true);
}
