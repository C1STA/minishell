/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:39:32 by wcista            #+#    #+#             */
/*   Updated: 2023/04/06 00:50:52 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

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

int	redir_parsing(t_redir *redir)
{
	int		i;
	bool	in;
	bool	out;

	i = 0;
	in = false;
	out = false;
	while (redir)
	{
		if (redir->in_file == 1)
		{
			in = true;
			out = false;
			i++;
			redir = redir->next_sibling;
			if (!redir_infile(redir))
				return (i);
		}
		else if (redir->heredoc == 1)
		{
			in = true;
			out = false;
			i++;
			redir = redir->next_sibling;
		}
		else if (redir->out_file == 1)
		{
			in = false;
			out = true;
			i++;
			redir = redir->next_sibling;
			if (!redir_outfile(redir))
				return (i);
		}
		else if (redir->append == 1)
		{
			in = false;
			out = true;
			i++;
			redir = redir->next_sibling;
			if (!redir_append(redir))
				return (i);
		}
		else if (redir->file == 1 && in == true)
		{
			if (!redir_file(redir))
				return (i);
		}
		i++;
		redir = redir->next_sibling;
	}
	return (i);
}

/* ft_putstr_fd("minishell: ", 2);
ft_putstr_fd(redir->txt, 2);
perror(": "); */

int	redir_last_infile(t_redir *redir, int i)
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
}

void	redir(t_redir *redir, t_indice *indice)
{
	//int	i;
	//int	i_infile;
	//int	i_outfile;

	indice->i = redir_parsing(redir);
	indice->i_infile = redir_last_infile(redir, indice->i);
	indice->i_outfile = redir_last_outfile(redir, indice->i);
	printf("i______________________________________________________ = %d\n", indice->i);
	printf("i_infile_______________________________________________ = %d\n", indice->i_infile);
	printf("i_outfile______________________________________________ = %d\n", indice->i_outfile);
}
