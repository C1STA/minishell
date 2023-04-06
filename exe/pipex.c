/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:47:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/05 20:30:50 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	close_unused_pipes(t_pipex *p, int i)
{
	int	j;

	j = 0;
	while (j < p->len + 1)
	{
		if (i != j)
		{
			printf("__________________________________Unused pipes : p->fd[%d][%d]\n", j, 0);
			close(p->fd[j][0]);
		}
		if (i + 1 != j)
		{
			printf("__________________________________Unused pipes : p->fd[%d][%d]\n", j, 1);
			close(p->fd[j][1]);
		}
		j++;
	}
}

static void	close_pipes_main(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->len + 1)
	{
		if (i != p->len + 1)
			close(p->fd[i][0]);
		if (i != 0)
			close(p->fd[i][1]);
		i++;
	}
}

static void	wait_childs(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->len)
	{
		waitpid(i, &g_exit_status, 0);
		i++;
	}
}

void	pipex(t_final *cmds, char *env[])
{
	t_pipex	*p;

	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		return ;
	p->len = lenlist(cmds);
	if (!init_pipes(p))
		return ;
	if (!init_forks(cmds, p, env))
		return ;
	/*Si besoin de quelque chose dans le process parent,
	on ne ferme que les pipes que l'on utilise pas en laissant
	ouvert que les pipes que l'on utilise.
	S'il n'y a besoin de rien faire dans le main, on peut fermer
	tous les fds.*/
	close_pipes_main(p);
	printf("\nHELLO\nWORLD\n");
	//close(p->fd[p->len][0]);
	//close(p->fd[0][1]);
	wait_childs(p);
	free(p);
}
