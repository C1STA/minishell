/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:19 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:31:20 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

bool	builtin_pwd(t_pipex *p)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		p->exit_status = 1;
		print_perror("error retrieving current directory: \
pwd: cannot access parent directories");
		return (true);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	p->exit_status = 0;
	return (true);
}
