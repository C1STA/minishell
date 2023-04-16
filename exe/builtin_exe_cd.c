/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:51:34 by wcista            #+#    #+#             */
/*   Updated: 2023/04/16 09:23:09 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

size_t	env_finder(char *name, char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && ft_strncmp(name, env[i], ft_strlen(name)))
		i++;
	return (i);
}

char	*get_env_input(char *variable, int j, char *env[])
{
	size_t	i;

	i = env_finder(variable, env);
	if (i == ft_tablen(env))
		return (NULL);
	return (&env[i][j]);
}

void	export_env(char *variable, char *val, char *env[])
{
	size_t	i;

	i = env_finder(variable, env);
	free(env[i]);
	env[i] = ft_strjoin_env(variable, val);
}

bool	first_check(t_final *cmds, t_pipex *p, char *env[], t_cd *cd)
{
	if (!cmds->cmds[1] || (cmds->cmds[1][0] == '~' \
	&& !cmds->cmds[1][1] && !cmds->cmds[2]))
	{
		cd->path = get_env_input("HOME=", 5, env);
		if (chdir(cd->path))
			return (print_perror_cd("HOME not set", false, p, cd));
		cd->cwd = get_env_input("PWD=", 4, env);
		export_env("OLDPWD=", cd->cwd, env);
		export_env("PWD=", cd->path, env);
		p->exit_status = 0;
		free(cd);
		return (false);
	}
	if (ft_tablen(cmds->cmds) > 2)
		return (print_perror_cd("too many arguments", false, p, cd));
	return (true);
}

void	free_cd(t_cd *cd)
{
	free(cd->tmp);
	free(cd->path);
	free(cd->cwd);
	free(cd);
}

bool	builtin_exe_cd(t_final *cmds, char *env[], t_pipex *p)
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
getcwd: cannot access parent directories", true, p, cd));
	cd->tmp = ft_strcpy(cd->cwd);
	if (cmds->cmds[1][0] != '/')
	{
		cd->cwd = ft_strjoin_free(cd->cwd, "/");
		cd->cwd = ft_strjoin_free(cd->cwd, cmds->cmds[1]);
		if (chdir(cd->cwd))
			return (print_perror_cd(cmds->cmds[1], true, p, cd));
	}
	else if (chdir(cmds->cmds[1]))
		return (print_perror_cd(cmds->cmds[1], true, p, cd));
	export_env("OLDPWD=", cd->tmp, env);
	free(cd->path);
	cd->path = NULL;
	cd->path = getcwd(cd->path, 0);
	export_env("PWD=", cd->path, env);
	p->exit_status = 0;
	return (free_cd(cd), true);
}
