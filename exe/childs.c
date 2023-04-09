/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:57:37 by wcista            #+#    #+#             */
/*   Updated: 2023/04/09 22:29:13 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

static t_final	*get_right_cmd(t_final *cmds, int i)
{
	int	j;

	j = 0;
	while (cmds)
	{
		if (j == i)
			return (cmds);
		cmds = cmds->next_sibling;
		j++;
	}
	return (cmds);
}

void	child_processs(t_final *cmds, t_pipex *p, int i, t_env *mini_env)
{
	(void)mini_env;
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;

	printf("LE PID DU PROCESSUS ENFANT EST : _______cmds: %d___________%d\n", i, getpid());
	close_unused_pipes(p, i);
	tmp_cmds = get_right_cmd(cmds, i);
	tmp_redir = tmp_cmds->redir;
	if (i != 0)
		dup2(p->fd[i - 1][0], STDIN_FILENO);
	if (i != p->nb_cmds - 1)
		dup2(p->fd[i][1], STDOUT_FILENO);
	//if (i == 0)
	//	p->fd[i][0] = STDIN_FILENO;
	//if (i == p->nb_cmds - 1)
	//	p->fd[i - 1][1] = STDOUT_FILENO;
	//if (final->cmds[0])
		//check s'il existe une commande
	//execve(tmp_cmds->cmds[0], tmp_cmds->cmds, NULL);
		ft_putstr_fd("EXECERROR\n", 2);
	if (tmp_redir)
	{
		if (!init_redir(tmp_redir, i))
		{
			if (i != p->nb_cmds - 1)
			{
				printf("_______________(cmd: %d)_____________________Used pipes : p->fd[%d][%d]\n",i,  i, 0);
				close(p->fd[i][0]);
			}
			if (i != 0)
			{
				printf("________________(cmd: %d)____________________Used pipes : p->fd[%d ][%d]\n",i,  i - 1, 1);
				close(p->fd[i - 1][1]);
			}
			free_pipex(p);
			free_exe(&cmds, &mini_env);
			exit(EXIT_FAILURE);
		}
	}
	ft_putstr_fd("\n\n\n", 2);
	ft_putstr_fd(tmp_cmds->cmds[0], 2);
	ft_putstr_fd("AFTER REDIR", 2);
	ft_putstr_fd("\n\n\n", 2);
	execvp(tmp_cmds->cmds[0], tmp_cmds->cmds);
/* 	if (execve(cmds->cmds[0], cmds->cmds, mini_env))
	{
		ft_putstr_fd("ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo", 2);
		ft_putstr_fd(cmds->cmds[0], 2);
		perror(": ");
	} */
	//printf("\ncmds_______is______________________%s__\n", cmds->cmds[0]);

	/*Appliquer les bons dup2 en fonction des redirections 
	Si pas de redir, on applique les bons dup2 dans la meme fonction*/

	/*On execute la commande avec ses arguments*/
	if (i != p->nb_cmds - 1)
	{
		printf("_______________(cmd: %d)_____________________Used pipes : p->fd[%d][%d]\n",i,  i, 0);
		close(p->fd[i][0]);
	}
	if (i != 0)
	{
		printf("________________(cmd: %d)____________________Used pipes : p->fd[%d ][%d]\n",i,  i - 1, 1);
		close(p->fd[i - 1][1]);
	}
	free_exe(&cmds, &mini_env);
	free_pipex(p);
	exit(EXIT_SUCCESS);
}
