/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:39:32 by wcista            #+#    #+#             */
/*   Updated: 2023/04/09 19:59:02 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

static bool	redir_in_here(t_redir *redir, int i, int j)
{
	if (redir->in_file == 1)
	{
		redir = redir->next_sibling;
		if (!redir_infile(redir))
			return (false);
	}
	if (redir->heredoc == 1)
	{
		redir = redir->next_sibling;
		if (!redir_heredoc(redir, i, j))
			return (false);
	}
	return (true);
}

static bool	redir_out_app(t_redir *redir)
{
	if (redir->out_file == 1)
	{
		redir = redir->next_sibling;
		if (!redir_outfile(redir))
			return (false);
	}
	if (redir->append == 1)
	{
		redir = redir->next_sibling;
		if (!redir_append(redir))
			return (false);
	}
	return (true);
}

bool	init_redir(t_redir *redir, int i)
{
	int		j;
	t_redir	*tmp_redir;

	j = 0;
	tmp_redir = redir;
	while (tmp_redir)
	{
		if (tmp_redir->in_file == 1 || tmp_redir->heredoc == 1)
		{
			if (!redir_in_here(tmp_redir, i, j))
				return (false);
		}
		else if (tmp_redir->out_file == 1 || tmp_redir->append == 1)
		{
			if (!redir_out_app(tmp_redir))
				return (false);
		}
		j++;
		tmp_redir = tmp_redir->next_sibling;
	}
	return (true);
}
