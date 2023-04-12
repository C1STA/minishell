/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:58:29 by wcista            #+#    #+#             */
/*   Updated: 2023/04/12 04:08:29 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	print_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	print_exec(char *s, t_pipex *p)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (s[0] != '/')
		ft_putstr_fd(": command not found\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	p->exit_status = 127;
}

void	print_exit(char *s, bool n, t_pipex *p)
{
	if (n)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		p->exit_status = 1;
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		p->exit_status = 2;
	}
}
