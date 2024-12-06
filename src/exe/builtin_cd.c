/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:51:34 by wcista            #+#    #+#             */
/*   Updated: 2024/12/06 15:53:26 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	first_check(t_final *cmds, t_pipex *p, char *env[], t_cd *cd)
{
	if (!cmds->cmds[1] || (cmds->cmds[1][0] == '~' \
	&& !cmds->cmds[1][1] && !cmds->cmds[2]))
	{
		cd->path = get_env_input("HOME=", 5, env);
		if (!cd->path)
			return (print_perror_cd("HOME not set", false, p, cd), false);
		if (chdir(cd->path))
			return (print_perror_cd("HOME not set", false, p, cd), false);
		cd->cwd = get_env_input("PWD=", 4, env);
		if (!cd->cwd)
			return (print_perror_cd("PWD not set", false, p, cd), false);
		if (!export_env("OLDPWD=", cd->cwd, env))
			return (print_perror_cd("OLDPWD not set", false, p, cd), false);
		if (!export_env("PWD=", cd->path, env))
			return (print_perror_cd("PWD not set", false, p, cd), false);
		p->exit_status = 0;
		return (free_cd(cd), false);
	}
	if (ft_tablen(cmds->cmds) > 2)
		return (print_perror_cd("too many arguments", false, p, cd), false);
	return (true);
}

static bool	cd_builtin(t_final *cmds, t_pipex *p, t_cd *cd)
{
	if (cmds->cmds[1][0] != '/')
	{
		cd->cwd = ft_strjoin_free(cd->cwd, "/");
		cd->cwd = ft_strjoin_free(cd->cwd, cmds->cmds[1]);
		if (chdir(cd->cwd))
			return (print_perror_cd(cmds->cmds[1], true, p, cd), false);
	}
	else if (chdir(cmds->cmds[1]))
		return (print_perror_cd(cmds->cmds[1], true, p, cd), false);
	return (true);
}

bool	builtin_cd(t_final *cmds, char *env[], t_pipex *p)
{
	t_cd	*cd;

	cd = (t_cd *)malloc(sizeof(t_cd));
	if (!cd)
		return (true);
	cd->path = NULL;
	cd->cwd = NULL;
	cd->tmp = NULL;
	if (!first_check(cmds, p, env, cd))
		return (true);
	cd->cwd = getcwd(cd->cwd, 0);
	if (!cd->cwd)
		return (print_perror_cd("error retrieving current directory: \
getcwd: cannot access parent directories", true, p, cd), true);
	cd->tmp = ft_strcpy(cd->cwd);
	if (!cd_builtin(cmds, p, cd))
		return (true);
	if (!export_env("OLDPWD=", cd->tmp, env))
		return (print_perror_cd("OLDPWD not set", false, p, cd), true);
	free(cd->path);
	cd->path = NULL;
	cd->path = getcwd(cd->path, 0);
	if (!export_env("PWD=", cd->path, env))
		return (print_perror_cd("PWD not set", false, p, cd), true);
	return (p->exit_status = 0, free_cd(cd), true);
}
