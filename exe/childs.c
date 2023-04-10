/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:57:37 by wcista            #+#    #+#             */
/*   Updated: 2023/04/10 22:53:01 by wcista           ###   ########.fr       */
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

	//printf("LE PID DU PROCESSUS ENFANT EST : _______cmds: %d___________%d\n", i, getpid());
	close_unused_pipes(p, i);
	tmp_cmds = get_right_cmd(cmds, i);
	tmp_redir = tmp_cmds->redir;
	if (i != 0)
		dup2(p->fd[i - 1][0], STDIN_FILENO);
	if (i != p->nb_cmds - 1)
	{
		dup2(p->fd[i][1], STDOUT_FILENO);
	}
	if (tmp_redir)
	{
		if (!init_redir(tmp_redir, i))
		{
			if (i != p->nb_cmds - 1)
			{
				//printf("_______________(cmd: %d)_____________________Used pipes : p->fd[%d][%d]\n",i,  i, 0);
				close(p->fd[i][0]);
			}
			if (i != 0)
			{
				//printf("________________(cmd: %d)____________________Used pipes : p->fd[%d ][%d]\n",i,  i - 1, 1);
				close(p->fd[i - 1][1]);
			}
			free_pipex(p);
			free_exe(&cmds, &mini_env);
			exit(g_exit_status);
		}
	}
	if (!builtin_exe(tmp_cmds))
	{
		if (execvp(tmp_cmds->cmds[0], tmp_cmds->cmds) == -1)
			print_perror(tmp_cmds->cmds[0]);
	}
	//ft_putstr_fd("\n\n\n", 2);
	//ft_putstr_fd(tmp_cmds->cmds[0], 2);
	//ft_putstr_fd("AFTER REDIR", 2);
	//ft_putstr_fd("\n\n\n", 2);
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
		//printf("_______________(cmd: %d)_____________________Used pipes : p->fd[%d][%d]\n",i,  i, 1);
		//ft_putstr_fd("________________(cmd: ", 2);
		//ft_putnbr_fd(i, 2);
		//ft_putstr_fd(")____________________Used pipes : p->fd[", 2);
		//ft_putnbr_fd(i, 2);
		//ft_putstr_fd("][1]\n", 2);
		close(p->fd[i][1]);
	}
	if (i != 0)
	{
		//printf("________________(cmd: %d)____________________Used pipes : p->fd[%d ][%d]\n",i,  i - 1, 0);
		//ft_putstr_fd("________________(cmd: ", 2);
		//ft_putnbr_fd(i, 2);
		//ft_putstr_fd(")____________________Used pipes : p->fd[", 2);
		//ft_putnbr_fd(i - 1, 2);
		//ft_putstr_fd("][0]\n\n", 2);
		
		close(p->fd[i - 1][0]);
	}
	free_exe(&cmds, &mini_env);
	free_pipex(p);
	exit(g_exit_status);
}
