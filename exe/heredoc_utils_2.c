/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 21:37:07 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/23 21:55:22 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int  g_exit_status;

void	print_eof(char *s)
{
	ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("')\n", 2);
}

bool	infinite_loop(char *env[], t_redir *redir, t_heredoc *h)
{
	while (1)
	{
		h->input = readline("> ");
		if (g_exit_status == 42)
			return (g_exit_status = 130, free_heredoc(h, false));
		if (!ft_strcmp(h->input, redir->txt))
			break ;
		if (!redir->quotes)
			h->input = heredoc_expand(h, env, false);
		if (!h->input)
			return (print_eof(redir->txt), g_exit_status = 0, \
			free_heredoc(h, false));
		h->reader = write(h->fd, h->input, ft_strlen(h->input));
		if (h->reader == -1)
			return (free_heredoc(h, false));
		h->reader = write(h->fd, "\n", 1);
		free(h->input);
		h->input = NULL;
	}
	return (true);
}
