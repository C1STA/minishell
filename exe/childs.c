/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:57:37 by wcista            #+#    #+#             */
/*   Updated: 2023/04/08 19:52:33 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

t_final	*get_right_cmd(t_final *cmds, int i)
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
	printf("LE PID DU PROCESSUS ENFANT EST : __________________%d\n", getpid());
	close_unused_pipes(p, i);
	cmds = get_right_cmd(cmds, i);
	dup2(p->fd[i][0], STDIN_FILENO);
	dup2(p->fd[i + 1][1], STDOUT_FILENO);
/* 	if (cmds->redir)
		if (!init_redir(cmds->redir, i));
		{
			free_pipex(p);
			free_exe(&cmds, &mini_env);
			exit(EXIT_FAILURE);
		} */
/* 	if (execve(cmds->cmds[0], cmds->cmds, mini_env))
	{
		ft_putstr_fd("ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo", 2);
		ft_putstr_fd(cmds->cmds[0], 2);
		perror(": ");
	} */
	printf("\ncmds_______is______________________%s__\n", cmds->cmds[0]);

	/*Appliquer les bons dup2 en fonction des redirections 
	Si pas de redir, on applique les bons dup2 dans la meme fonction*/

	/*On execute la commande avec ses arguments*/
	printf("____________________________________Used pipes : p->fd[%d][%d]\n", i, 0);
	close(p->fd[i][0]);
	printf("____________________________________Used pipes : p->fd[%d ][%d]\n", i + 1, 1);
	close(p->fd[i + 1][1]);
	exit(EXIT_SUCCESS);
}
