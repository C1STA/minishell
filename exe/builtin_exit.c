/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:31:22 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 15:24:42 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	ft_exit_d(t_env **env)
{
	free_env(env);
	ft_putstr_fd("exit\n", 1);
	exit (g_exit_status);
}

static void	builtin_exit_bis(t_final *cmds, t_pipex *p)
{
	long long	tmp;

	ft_putstr_fd("exit\n", 1);
	if (cmds->cmds[1][0] == '-')
	{
		tmp = ft_atol_minus(cmds->cmds[1]);
		if (tmp > 0)
			return (print_exit(cmds, p, cmds->cmds[1], false));
	}
	else
	{
		tmp = ft_atol_plus(cmds->cmds[1]);
		if (tmp < 0)
			return (print_exit(cmds, p, cmds->cmds[1], false));
	}
	p->exit_status = (int)tmp;
	if (p->nb_cmds == 1)
		remove_heredoc(cmds);
}

bool	exit_return(t_final *cmds, char *env[], t_pipex *p)
{
	if (p->nb_cmds == 1)
		remove_heredoc(cmds);
	ft_putstr_fd("exit\n", 1);
	exit_exe(cmds, env, p);
	return (true);
}

bool	builtin_exit(t_final *cmds, char *env[], t_pipex *p)
{
	int				i;
	int				j;

	if (!cmds->cmds[1])
		return (exit_return(cmds, env, p));
	i = 1;
	while (cmds->cmds[i])
	{
		j = 0;
		if (i > 1)
			return (print_exit(cmds, p, NULL, true), true);
		if ((cmds->cmds[i][j] == '-' || cmds->cmds[i][j] == '+') \
		&& cmds->cmds[i][j + 1])
			j++;
		while (cmds->cmds[i][j])
		{
			if (!ft_isdigit(cmds->cmds[i][j]))
				return (print_exit(cmds, p, cmds->cmds[i], false), \
				exit_exe(cmds, env, p), true);
			j++;
		}
		i++;
	}
	builtin_exit_bis(cmds, p);
	return (exit_exe(cmds, env, p), true);
}
