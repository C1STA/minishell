/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:19:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/12 06:24:16 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	executor(t_final *cmds, t_env *mini_env)
{
	//t_final	*tmp_cmds;

	//tmp_cmds = cmds;
	cmds->exit_tmp = g_exit_status;
	if (!ft_heredoc(cmds, mini_env))
		return ;
	//tmp_cmds = cmds;
	pipex(cmds, mini_env);
	//printf("LE PID DU PROCESSUS PARENT EST : __________________%d\n", getpid());
	//tmp_cmds = cmds;
	remove_heredoc(cmds);
	//printf("\n");
}
