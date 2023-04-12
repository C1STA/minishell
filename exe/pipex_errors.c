/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:09:51 by wcista            #+#    #+#             */
/*   Updated: 2023/04/12 15:49:54 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

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
	print_perror("pipe");
	free_pipex(p);
	return (false);
}

bool	fork_error(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
	print_perror("fork");
	free_pipex(p);
	return (false);
}
