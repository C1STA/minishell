/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:25 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:30:26 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	free_cd(t_cd *cd)
{
	if (cd->tmp)
		free(cd->tmp);
	if (cd->path)
		free(cd->path);
	if (cd->cwd)
		free(cd->cwd);
	free(cd);
}

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
	char	*dest;

	i = env_finder(variable, env);
	if (i == ft_tablen(env))
		return (NULL);
	dest = ft_strdup(&env[i][j]);
	return (dest);
}

bool	export_env(char *variable, char *val, char *env[])
{
	size_t	i;

	i = env_finder(variable, env);
	if (i == ft_tablen(env))
		return (false);
	free(env[i]);
	env[i] = ft_strjoin_env(variable, val);
	return (true);
}
