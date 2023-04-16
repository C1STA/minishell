/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:28:33 by wcista            #+#    #+#             */
/*   Updated: 2023/04/16 08:55:14 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

void	remove_heredoc(t_final *cmds)
{
	int		i;
	int		j;
	char	*file_name;
	t_redir	*redir;

	i = 0;
	while (cmds)
	{
		j = 0;
		redir = cmds->redir;
		while (redir)
		{
			if (redir->heredoc == 1)
			{
				file_name = heredoc_file_name(i, j);
				unlink(file_name);
				free(file_name);
			}
			j++;
			redir = redir->next;
		}
		i++;
		cmds = cmds->next;
	}
}
