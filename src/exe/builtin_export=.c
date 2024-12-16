/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export=.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:08 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:31:10 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	is_export_or_unset_all(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "export=", 7) || !(ft_strncmp(s[i], "unset=", 6)))
			count++;
		i++;
	}
	if (count == i)
		return (true);
	return (false);
}

bool	builtin_exp_equl(t_final *cmds, t_pipex *p)
{
	int	i;
	int	j;

	if (is_export_or_unset_all(cmds->cmds))
		return (p->exit_status = 0, true);
	i = 0;
	j = 0;
	while (cmds->cmds[i])
	{
		if (!ft_strncmp(cmds->cmds[i], "export=\
", 7) || !ft_strncmp(cmds->cmds[i], "unset=", 6))
			free(cmds->cmds[i]);
		else
		{
			while (cmds->cmds[i])
			{
				cmds->cmds[j] = cmds->cmds[i];
				i++;
				j++;
			}
			break ;
		}
		i++;
	}
	cmds->cmds[j] = NULL;
	return (false);
}
