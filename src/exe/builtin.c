/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:50:34 by wcista            #+#    #+#             */
/*   Updated: 2024/11/07 19:26:04 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	builtin_exit_status(t_pipex *p)
{
	ft_putnbr_fd(p->exit_status, 2);
	ft_putstr_fd(": command not found\n", 2);
	p->exit_status = 127;
	return (true);
}

static bool	builtin_export_unset(t_pipex *p)
{
	p->exit_status = 0;
	return (true);
}

bool	builtin(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		return (builtin_exit(cmds, env, p, m));
	if (!ft_strcmp(cmds->cmds[0], "echo"))
		return (builtin_echo(cmds, p));
	if (!ft_strcmp(cmds->cmds[0], "$?"))
		return (builtin_exit_status(p));
	if (!ft_strcmp(cmds->cmds[0], "unset"))
		return (builtin_export_unset(p));
	if (!ft_strcmp(cmds->cmds[0], "cd"))
		return (builtin_cd(cmds, env, p));
	if (!ft_strcmp(cmds->cmds[0], "pwd"))
		return (builtin_pwd(p));
	if ((!ft_strcmp(cmds->cmds[0], "export")) && !cmds->cmds[1])
		return (builtin_export(env, p));
	if ((!ft_strcmp(cmds->cmds[0], "export")) && cmds->cmds[1])
		return (builtin_export_unset(p));
	if ((!ft_strcmp(cmds->cmds[0], "env")) && !cmds->cmds[1])
		return (builtin_env(env, p));
	return (false);
}

bool	isbuiltin(t_final *cmds)
{
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		return (true);
	if (!ft_strcmp(cmds->cmds[0], "cd"))
		return (true);
	if ((!ft_strcmp(cmds->cmds[0], "export")) && !cmds->cmds[1])
		return (true);
	if ((!ft_strcmp(cmds->cmds[0], "env")) && !cmds->cmds[1])
		return (true);
	if (!ft_strcmp(cmds->cmds[0], "pwd"))
		return (true);
	return (false);
}
