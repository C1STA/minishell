/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lonely.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:01:07 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 13:43:03 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

static void	lonely_exit(t_pipex *p, int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	g_exit_status = p->exit_status;
	free_pipex(p);
}

void	lonely_builtin(t_final *cmds, char *env[], t_pipex *p)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!init_redir(cmds->redir, p))
		lonely_exit(p, saved_stdin, saved_stdout);
	if (!ft_strcmp(cmds->cmds[0], "exit"))
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	builtin(cmds, env, p);
	lonely_exit(p, saved_stdin, saved_stdout);
}
