/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:19:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/10 15:12:02 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	executor(t_final *cmds, t_env *mini_env)
{
	//t_final	*tmp_cmds;

	//tmp_cmds = cmds;
	if (!ft_heredoc(cmds, mini_env))
		return ;
	//tmp_cmds = cmds;
	pipex(cmds, mini_env);
	//printf("LE PID DU PROCESSUS PARENT EST : __________________%d\n", getpid());
	//tmp_cmds = cmds;
	remove_heredoc(cmds);
	//printf("\n");
}
