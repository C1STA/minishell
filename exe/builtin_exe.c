/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:50:34 by wcista            #+#    #+#             */
/*   Updated: 2023/04/13 21:24:33 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	builtin_exe_exit_bis(t_final *cmds, t_pipex *p)
{
	long long	tmp;

	if (cmds->cmds[1][0] == '-')
	{
		tmp = ft_atol_minus(cmds->cmds[1]);
		if (tmp > 0)
			return (print_exit(cmds->cmds[1], false, p));
	}
	else
	{
		tmp = ft_atol_plus(cmds->cmds[1]);
		if (tmp < 0)
			return (print_exit(cmds->cmds[1], false, p));
	}
	p->exit_status = (int)tmp;
}

bool	builtin_exe_exit(t_final *cmds, t_pipex *p)
{
	int				i;
	int				j;

	if (!cmds->cmds[1])
		return (true);
	i = 1;
	while (cmds->cmds[i])
	{
		j = 0;
		if (i > 1)
			return (print_exit(NULL, true, p), true);
		if ((cmds->cmds[i][j] == '-' || cmds->cmds[i][j] == '+') \
		&& cmds->cmds[i][j + 1])
			j++;
		while (cmds->cmds[i][j])
		{
			if (!ft_isdigit(cmds->cmds[i][j]))
				return (print_exit(cmds->cmds[i], false, p), true);
			j++;
		}
		i++;
	}
	builtin_exe_exit_bis(cmds, p);
	return (true);
}

bool	builtin_exe_echo(t_final *cmds, t_pipex *p)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	p->exit_status = 0;
	if (!cmds->cmds[1])
		return (printf("\n"), true);
	if (!ft_strcmp(cmds->cmds[i], "-n"))
	{
		n = true;
		i++;
	}
	while (cmds->cmds[i])
	{
		printf("%s", cmds->cmds[i]);
		if (cmds->cmds[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	return (true);
}

bool	builtin_exit_status(t_pipex *p)
{
	ft_putnbr_fd(p->exit_status, 2);
	ft_putstr_fd(": command not found\n", 2);
	p->exit_status = 127;
	return (true);
}

bool	builtin_exe_unset(t_pipex *p)
{
	p->exit_status = 0;
	return (true);
}

bool	builtin_exe(t_final *cmds, t_pipex *p)
{
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		return (builtin_exe_exit(cmds, p));
	if (!ft_strcmp(cmds->cmds[0], "echo"))
		return (builtin_exe_echo(cmds, p));
	if (!ft_strcmp(cmds->cmds[0], "$?"))
		return (builtin_exit_status(p));
	if (!ft_strcmp(cmds->cmds[0], "unset"))
		 return (builtin_exe_unset(p));
	//if ((!ft_strcmp(cmds->cmds[0], "export")) && cmds->cmds[1])
		// PRINT ENV A -> Z --> check redirections (export sans options)
	//if((!ft_strcmp(cmds->cmds[0], "export")) && !cmds->cmds[1])
		// EXIT AVEC LES BONS PIPES (pass) (export avec options)
	//if (!ft_strcmp(cmds->cmds[0], "env"))
		//print env --> check redirections
	return (false);
}
