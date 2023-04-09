/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:28:49 by wcista            #+#    #+#             */
/*   Updated: 2023/04/08 19:48:08 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

static void	ft_free_str(char **str)
{
	if (str != NULL && **str != '\0')
	{
		free(*str);
		*str = NULL;
	}
}

void	free_exe(t_final **cmds, t_env **mini_env)
{
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;
	t_redir	*redir_free;
	int		i;

	while (*cmds)
	{
		i = 0;
		tmp_cmds = (*cmds)->next_sibling;
		tmp_redir = (*cmds)->redir;
		while (tmp_redir)
		{
			redir_free = tmp_redir;
			tmp_redir = tmp_redir->next_sibling;
			ft_free_str(&redir_free->txt);
			free(redir_free);
		}
		while ((*cmds)->cmds[i])
			free((*cmds)->cmds[i++]);
		free((*cmds)->cmds);
		free(*cmds);
		*cmds = tmp_cmds;
	}
	free_env(mini_env);
}
