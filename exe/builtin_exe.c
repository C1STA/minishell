/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:50:34 by wcista            #+#    #+#             */
/*   Updated: 2023/04/10 23:00:47 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	builtin_exe_exit(t_final *cmds)
{
	int		i;
	int		j;

	if (!cmds->cmds[1])
		return (true);
	i = 1;
	while (cmds->cmds[i])
	{
		j = 0;
		if (i > 1)
			return (print_exit(NULL, true), true);
		while (cmds->cmds[i][j])
		{
			if (!ft_isdigit(cmds->cmds[i][j]))
				return (print_exit(cmds->cmds[i], false), true);
			j++;
		}
		i++;
	}
	g_exit_status = ft_atoi(cmds->cmds[i - 1]);
	return (true);
}

bool	builtin_exe_echo(t_final *cmds)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
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

bool	builtin_exe(t_final *cmds)
{
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		return (builtin_exe_exit(cmds));
	if (!ft_strcmp(cmds->cmds[0], "echo"))
		return (builtin_exe_echo(cmds));
	//if ((!ft_strcmp(cmds->cmds[0], "export")) && cmds->cmds[1])
		// PRINT ENV A -> Z --> check redirections (export sans options)
	//if((!ft_strcmp(cmds->cmds[0], "export")) && !cmds->cmds[1])
		// EXIT AVEC LES BONS PIPES (pass) (export avec options)
	//if (!ft_strcmp(cmds->cmds[0], "unset"))
		// EXIT AVEC LES BONS PIPES (pass)
	//if (!ft_strcmp(cmds->cmds[0], "env"))
		//print env --> check redirections
	return (false);
}
