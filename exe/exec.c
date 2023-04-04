/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:19:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 05:23:46 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

void	executor(t_final *cmds, t_env *env)
{
	//t_indice	*indice;

	if (!ft_heredoc(cmds))
		return ;
	//indice = (t_indice *)malloc(sizeof(t_indice));
	//if (cmds->redir)
	//	redir(cmds->redir, indice);
	//printf("INDICE ==================%d\n", indice->i);
	pipex(cmds, env);
}
