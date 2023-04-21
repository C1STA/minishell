/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 03:00:43 by wcista            #+#    #+#             */
/*   Updated: 2023/04/21 06:41:54 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

static char	**get_path_tab(char *env[])
{
	int		i;
	char	*path_line;
	char	**path;

	i = 0;
	path_line = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_line = ft_substr(env[i], 5, ft_strlen(env[i]));
			break ;
		}
		i++;
	}
	if (!path_line)
		return (NULL);
	path = ft_split(path_line, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin_free(path[i], "/");
		i++;
	}
	return (free(path_line), path);
}

static bool	raw_access(t_final *cmds)
{
	if (!access(cmds->cmds[0], F_OK | X_OK))
		return (true);
	return (false);
}

static void	init_access(t_final *cmds, char **path)
{
	int		i;
	char	*cmd_tmp;

	i = 0;
	cmd_tmp = NULL;
	while (path[i])
	{
		cmd_tmp = ft_strjoin(path[i], cmds->cmds[0]);
		if (!access(cmd_tmp, F_OK | X_OK))
			cmds->cmds[0] = ft_strcpy(cmd_tmp);
		free(cmd_tmp);
		cmd_tmp = NULL;
		i++;
	}
	if (cmd_tmp)
		free(cmd_tmp);
	free(path);
}

void	is_access(t_final *cmds, char *env[])
{
	char	**path;

	if (!raw_access(cmds))
	{
		path = get_path_tab(env);
		if (!path)
			return ;
		init_access(cmds, path);
	}
}
