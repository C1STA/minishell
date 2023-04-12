/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:09:51 by wcista            #+#    #+#             */
/*   Updated: 2023/04/12 06:40:58 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

void	free_pipex(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		if (p->fd[i])
			free(p->fd[i]);
		i++;
	}
	free(p->fd);
	if (p->child)
		free(p->child);
	free(p);
}

bool	pipe_error(t_pipex *p)
{
	while (p->i >= 0)
	{
		close(p->fd[p->i][0]);
		close(p->fd[p->i][1]);
		p->i--;
	}
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
