/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:46:07 by wcista            #+#    #+#             */
/*   Updated: 2023/04/23 02:06:15 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	n_arg(t_final *cmds)
{
	int	i;
	int	len;

	if (cmds->cmds[1][0] != '-' || !cmds->cmds[1][1])
		return (false);
	i = 1;
	len = (int)ft_strlen(cmds->cmds[1]);
	while (i < len)
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
	p->exit_status = 0;
	if (!cmds->cmds[1])
		return (ft_putstr_fd("\n", 1), true);
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
	return (true);
}
