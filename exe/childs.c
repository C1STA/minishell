/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:57:37 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 20:04:18 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

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

void	child_processs(t_final *cmds, t_pipex *p, int i)
{
	printf("LE PID DU PROCESSUS ENFANT EST : __________________%d\n", getpid());
	close_unused_pipes(p, i);
	cmds = get_right_cmd(cmds, i);
	printf("\ncmds_______is______________________%s__\n", cmds->cmds[0]);
	//execve(cmds->cmds[0], cmds->cmds, env);

	/*Appliquer les bons dup2 en fonction des redirections 
	Si pas de redir, on applique les bons dup2 dans la meme fonction*/

	/*On execute la commande avec ses arguments*/
	close(p->fd[i][0]);
	close(p->fd[i][1]);
	exit(EXIT_SUCCESS);
}
