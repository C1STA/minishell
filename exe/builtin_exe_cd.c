/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:51:34 by wcista            #+#    #+#             */
/*   Updated: 2023/04/15 16:33:51 by wcista           ###   ########.fr       */
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

char	*get_env_input(char *variable, int j, t_env *mini_env)
{
	size_t	i;

	i = env_finder(variable, mini_env->env);
	if (i == ft_tablen(mini_env->env))
		return (NULL);
	return (&mini_env->env[i][j]);
}

void	export_env(char *variable, char *value, t_env *mini_env)
{
	size_t	i;

	i = env_finder(variable, mini_env->env);
	free(mini_env->env[i]);
	mini_env->env[i] = ft_strjoin(variable, value);
}

bool	check_args(t_final *cmds, t_pipex *p, t_env *mini_env, t_cd *cd)
{
	if (!cmds->cmds[1] || (cmds->cmds[1][0] == '~' \
	&& !cmds->cmds[1][1] && !cmds->cmds[2]))
	{
		cd->path = get_env_input("HOME=", 5, mini_env);
		if (!chdir(cd->path))
			return (print_perror_cd("HOME not set", false, p, cd));
		cd->pwd = get_env_input("PWD=", 4, mini_env);
		export_env("OLDPWD=", cd->pwd, mini_env);
		export_env("PWD=", cd->path, mini_env);
		p->exit_status = 0;
		return (false);
	}
	if (ft_tablen(cmds->cmds) > 2)
		return (print_perror_cd("too many arguments", false, p, cd));
	return (true);
}

bool	builtin_exe_cd(t_final *cmds, t_pipex *p, t_env *mini_env)
{
	t_cd	*cd;

	cd = (t_cd *)malloc(sizeof(t_cd));
	if (!cd)
		return (true);
	cd->path = NULL;
	if (!first_check(cmds, p, mini_env, cd))
		return (true);
	if (cmds->cmds[1][0] != '/')
	{
		cd->path = ft_strjoin_free(cd->path, "/");
		cd->path = ft_strjoin_free(cd->path, cmds->cmds[1]);
		if (!chdir(cd->path))
			return (print_perror_cd(cmds->cmds[1], true, p, cd));
	}
	else if (!chdir(cmds->cmds[1]))
		return (print_perror_cd(cmds->cmds[1], true, p, cd));
	cd->pwd = get_env_input("PWD=", 4, mini_env);
	export_env("OLDPWD=", cd->pwd, mini_env);
	cd->path = getcwd(cd->path, 0);
	export_env("PWD=", cd->path, mini_env);
	return (free(cd->path), free(cd), false);
}
