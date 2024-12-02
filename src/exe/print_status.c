/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:58:29 by wcista            #+#    #+#             */
/*   Updated: 2024/11/24 03:49:59 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	print_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	print_perror_cd(char *s, bool n, t_pipex *p, t_cd *cd)
{
	p->exit_status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	if (n)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
		ft_putstr_fd("\n", 2);
	if (cd->path)
		free(cd->path);
	if (cd->cwd)
		free(cd->cwd);
	if (cd->tmp)
		free(cd->tmp);
	free(cd);
}

static bool	slash_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '/')
			return (false);
		i++;
	}
	return (true);
}

void	print_exec(char *s, t_pipex *p)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (s[0] == '/')
	{
		if (slash_check(s))
		{
			ft_putstr_fd(": Is a directory\n", 2);
			p->exit_status = 126;
		}
		else
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			p->exit_status = 127;
		}
	}
	else
	{
		ft_putstr_fd(": command not found\n", 2);
		p->exit_status = 127;
	}
}

void	print_exit(t_final *cmds, t_pipex *p, char *s, bool n)
{
	ft_putstr_fd("exit\n", 1);
	if (n)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		p->exit_status = 1;
	}
	else
	{
		if (p->nb_cmds == 1)
			remove_heredoc(cmds);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		p->exit_status = 2;
	}
}
