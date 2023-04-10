/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 23:44:10 by wcista            #+#    #+#             */
/*   Updated: 2023/04/10 20:16:46 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	redir_infile(t_redir *redir)
{
	if (!redir)
		return (false);
	redir->fd_in = open(redir->txt, O_RDONLY);
	if (redir->fd_in == -1)
	{
		g_exit_status = 1;
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_in, STDIN_FILENO);
	close(redir->fd_in);
	return (true);
}

bool	redir_heredoc(t_redir *redir, int i, int j)
{
	char	*file_name;

	if (!redir)
		return (false);
	file_name = heredoc_file_name(i, j);
	redir->fd_in = open(file_name, O_RDONLY);
	if (redir->fd_in == -1)
	{
		g_exit_status = 1;
		return (print_perror(file_name), free(file_name), false);
	}
	dup2(redir->fd_in, STDIN_FILENO);
	close(redir->fd_in);
	free(file_name);
	return (true);
}

bool	redir_outfile(t_redir *redir)
{
	if (!redir)
		return (false);
	redir->fd_out = open(redir->txt, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (redir->fd_out == -1)
	{
		g_exit_status = 1;
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_out, STDOUT_FILENO);
	close(redir->fd_out);
	return (true);
}

bool	redir_append(t_redir *redir)
{
	redir->fd_out = open(redir->txt, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (redir->fd_out == -1)
	{
		g_exit_status = 1;
		return (print_perror(redir->txt), false);
	}
	if (access(redir->txt, W_OK) == -1)
	{
		g_exit_status = 1;
		close(redir->fd_out);
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_out, STDOUT_FILENO);
	close(redir->fd_out);
	return (true);
}
