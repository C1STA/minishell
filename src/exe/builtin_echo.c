/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:38 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:30:40 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

bool	n_arg(t_final *cmds)
{
	int	i;

	if (cmds->cmds[1][0] != '-' || !cmds->cmds[1][1])
		return (false);
	i = 1;
	while (cmds->cmds[1][i])
	{
		if (cmds->cmds[1][i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	builtin_echo(t_final *cmds, t_pipex *p)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	if (!cmds->cmds[1])
		return (p->exit_status = 0, ft_putstr_fd("\n", 1), true);
	if (n_arg(cmds))
	{
		n = true;
		i++;
	}
	while (cmds->cmds[i])
	{
		ft_putstr_fd(cmds->cmds[i], 1);
		if (cmds->cmds[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	p->exit_status = 0;
	return (true);
}
