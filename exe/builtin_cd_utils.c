/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:15:00 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 13:31:59 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	free_cd(t_cd *cd)
{
	free(cd->tmp);
	free(cd->path);
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
