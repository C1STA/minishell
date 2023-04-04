/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:09:51 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 03:41:03 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

void	free_pipex(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->fd[i])
	{
		free(p->fd[i]);
		i++;
	}
	free(p->fd);
	free(p);
}

bool	pipe_error(t_pipex *p, int i)
{
	while (i >= 0)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i--;
	}
	free_pipex(p);
	perror("minishell: pipe error");
	return (false);
}

bool	fork_error(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->len + 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
	free_pipex(p);
	perror("minishell: fork error");
	return (false);
}
