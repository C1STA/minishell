/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:19:53 by wcista            #+#    #+#             */
/*   Updated: 2024/11/07 19:26:04 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	executor(t_final *cmds, char *env[], t_main *m)
{
	cmds->exit_tmp = g_exit_status;
	if (!ft_heredoc(cmds, env, m))
		return (remove_heredoc(cmds));
	pipex(cmds, env, m);
	remove_heredoc(cmds);
}
