/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:54:37 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 13:55:01 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

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
	printf("%s\n", pwd);
	free(pwd);
	p->exit_status = 0;
	return (true);
}
