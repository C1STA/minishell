/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:47:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/09 22:19:51 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	close_unused_pipes(t_pipex *p, int i)
{
	int	j;

	j = 0;
	printf("\n_________________________________Commande : %d\n", i);
	while (j < p->nb_cmds - 1)
	{
		if (i != j)
		{
			printf("________________(cmd: %d)__________________Unused pipes : p->fd[%d][%d]\n",i, j, 0);
			close(p->fd[j][1]);
		}
		if (i - 1 != j)
		{
			printf("________________(cmd: %d)__________________Unused pipes : p->fd[%d][%d]\n",i,  j, 1);
			close(p->fd[j][0]);
		}
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
		waitpid(i, &g_exit_status, 0);
		printf("WAIT PROCESSUS = %d\n", i);
		i++;
	}
}

void	pipex(t_final *cmds, t_env *mini_env)
{
	t_pipex	*p;

	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		return ;
	p->nb_cmds = lenlist(cmds);
	if (!init_pipes(p))
		return ;
	if (!init_forks(cmds, p, mini_env))
		return ;
	close_pipes_main(p);
	wait_childs(p);
	free_pipex(p);
}
