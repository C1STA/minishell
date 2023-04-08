/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:39:32 by wcista            #+#    #+#             */
/*   Updated: 2023/04/07 17:58:04 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

void	print_perror(char *s)
{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
		perror("");
}

bool	redir_infile(t_redir *redir)
{
	if (!redir)
		return (false);
	redir->fd_in = open(redir->txt, O_RDONLY);
	if (redir->fd_in == -1)
		return (print_perror(redir->txt), false);
	dup2(redir->fd_in, STDIN_FILENO);
	close(redir->fd_in);
	return (true);
}

bool	redir_heredoc(t_redir *redir, int i, int j)
{
	char	*file_name;

	if(!redir)
		return (false);
	file_name = heredoc_file_name(i, j);
	redir->fd_in = open(file_name, O_RDONLY);
	if (redir->fd_in == -1)
		return (print_perror(file_name), free(file_name), false);
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
		return (print_perror(redir->txt), false);
	dup2(redir->fd_out, STDOUT_FILENO);
	close(redir->fd_out);
	return (true);
}

bool	redir_append(t_redir *redir)
{
	redir->fd_out = open(redir->txt, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (redir->fd_out == -1)
		return (print_perror(redir->txt), false);
	if (access(redir->txt, W_OK) == -1)
	{
		close(redir->fd_out);
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_out, STDOUT_FILENO);
	close(redir->fd_out);
	return (true);
}

/* bool	redir_file(t_redir *redir)
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
} */

bool	redir_in_here(t_redir *redir, int i, int j)
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

bool	redir_out_app(t_redir *redir)
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

/* int	redir_last_infile(t_redir *redir, int i)
{
	int	j;
	int	k;

	j = 0;
	k = -1;
	while (j < i)
	{
		if (redir->in_file == 1)
		{
			k = j;
			j++;
			redir = redir->next_sibling;
		}
		else if (redir->heredoc == 1)
		{
			k = j;
			j++;
			redir = redir->next_sibling;
		}
		j++;
		redir = redir->next_sibling;
	}
	return (k);
}

int		redir_last_outfile(t_redir *redir, int i)
{
	int	j;
	int	k;

	j = 0;
	k = -1;
	while (j < i)
	{
		if (redir->out_file == 1)
		{
			k = j;
			j++;
			redir = redir->next_sibling;
		}
		if (redir->append == 1)
		{
			k = j;
			j++;
			redir = redir->next_sibling;
		}
		j++;
		redir = redir->next_sibling;
	}
	return (k);
} */
