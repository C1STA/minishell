/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:09:51 by wcista            #+#    #+#             */
/*   Updated: 2023/04/24 21:26:31 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	free_pipex(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->fd)
	{
		while (i < p->nb_cmds - 1)
		{
			if (p->fd[i] != NULL)
				free(p->fd[i]);
			else
				break ;
			i++;
		}
		free(p->fd);
		p->fd = NULL;
	}
	if (p->child != NULL)
	{
		free(p->child);
		p->child = NULL;
	}
	free(p);
	p = NULL;
}

bool	pipe_error(t_pipex *p, int i)
{
	int	tmp;

	tmp = i + 1;
	while (i >= 0)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i--;
	}
	i = 0;
	while (i <= tmp)
	{
		free(p->fd[i]);
		i++;
	}
	free(p->fd);
	p->fd = NULL;
	print_perror("start_pipeline: pgrp pipe");
	free_pipex(p);
	g_exit_status = 24;
	return (false);
}

bool	fork_error(t_pipex *p)
{
	int	i;

	i = 0;
	ft_signal(1);
	while (i < p->nb_cmds - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
	print_perror("fork: retry");
	free_pipex(p);
	g_exit_status = 11;
	return (false);
}
