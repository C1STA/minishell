/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:26:21 by imrane            #+#    #+#             */
/*   Updated: 2023/04/01 18:32:14 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	ft_test(int sigint, siginfo_t *pid, void *idontknow)
{
	(void) idontknow;
	(void) sigint;
	(void) pid;
	write(1, "\n", 2);
	write(1, "bonjour\n", 8);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
} */

void	ft_sigint1(int sig)
{
	if (sig == 2)
	{
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	}
}

void	ft_signal(int i)
{
	if (i == 1)
	{
		signal(SIGINT, ft_sigint1);
		signal(SIGQUIT, SIG_IGN);
	}
}
