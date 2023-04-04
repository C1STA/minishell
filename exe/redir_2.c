/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 23:44:10 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 02:05:39 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	redir_infile(t_redir *redir)
{
	if (!redir)
		return (false);
	redir->fd_in = open(redir->txt, O_RDONLY);
	if (redir->fd_in == -1)
		return (false);
	if (access(redir->txt, R_OK) == -1)
	{
		close(redir->fd_in);
		return (false);
	}
	close(redir->fd_in);
	return (true);
}

bool	redir_outfile(t_redir *redir)
{
	if (!redir)
		return (false);
	redir->fd_out = open(redir->txt, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (redir->fd_out == -1)
		return (false);
	if (access(redir->txt, W_OK) == -1)
	{
		close (redir->fd_out);
		return (false);
	}
	close(redir->fd_out);
	return (true);
}

bool	redir_append(t_redir *redir)
{
	redir->fd_out = open(redir->txt, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (redir->fd_out == -1)
		return (false);
	if (access(redir->txt, W_OK) == -1)
	{
		close(redir->fd_out);
		return (false);
	}
	close(redir->fd_out);
	return (true);
}

bool	redir_file(t_redir *redir)
{
	redir->fd_in = open(redir->txt, O_RDONLY);
	if (redir->fd_in == -1)
		return (false);
	if (access(redir->txt, R_OK) == -1)
	{
		close(redir->fd_in);
		return (false);
	}
	close(redir->fd_in);
	return (true);
}
