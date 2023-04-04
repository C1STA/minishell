/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 20:49:17 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 02:13:04 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

/* static void	heredoc_signal(int sigint, siginfo_t *pid, void *idontknow)
{
	(void) idontknow;
	(void) sigint;
	(void) pid;
	t_final	*tmp;

	tmp = idontknow;
	write(1, "\n", 2);
	write(1, "xxheredoc\n", 10);
	remove_heredoc(tmp);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	reset_signal();
	exit(EXIT_SUCCESS);
}

void	declare_heredoc_signal(t_final *cmds)
{
	struct sigaction	heredoc_exit;
	sigset_t			heredoc_sigmask;

	sigemptyset(&heredoc_sigmask);
	heredoc_exit.sa_flags = SA_SIGINFO;
	heredoc_exit.sa_mask = heredoc_sigmask;
	heredoc_exit.sa_sigaction = heredoc_signal(SIGINT, &cmds, &cmds);
	sigaction(SIGINT, &heredoc_exit, NULL);
}

void	reset_signal(void)
{
	struct sigaction	action_e;
	sigset_t			sig_m;

	sigemptyset(&sig_m);
	action_e.sa_flags = SA_SIGINFO;
	action_e.sa_mask = sig_m;
	action_e.sa_sigaction = ft_sigint;
	sigaction(SIGINT, &action_e, NULL);
} */
