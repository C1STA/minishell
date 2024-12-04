/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:46:07 by wcista            #+#    #+#             */
/*   Updated: 2024/12/03 16:08:50 by wacista          ###   ########.fr       */
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

void	putecho(char *s, t_pipex *p)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			ft_putnbr_fd(p->exit_status, 1);
			i += 2;
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			i++;
		}
	}
}

bool	builtin_echo(t_final *cmds, t_pipex *p)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	if (!cmds->cmds[1])
	{
		p->exit_status = 0;
		return (ft_putstr_fd("\n", 1), true);
	}
	if (n_arg(cmds))
	{
		n = true;
		i++;
	}
	while (cmds->cmds[i])
	{
		//ft_putstr_fd(cmds->cmds[i], 1);
		putecho(cmds->cmds[i], p);
		if (cmds->cmds[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	p->exit_status = 0;
	return (true);
}
