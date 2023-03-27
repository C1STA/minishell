/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:16:50 by wcista            #+#    #+#             */
/*   Updated: 2023/03/27 19:23:45 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	free_heredoc(t_heredoc *h, bool n)
{
	if (h->fd)
		close(h->fd);
	if (h->file_name)
		free(h->file_name);
	if (h->input)
		free(h->input);
	if (h)
		free(h);
	return (n);
}

static char	*heredoc_file_name(int i, int j)
{
	char	*k;
	char	*l;
	char	*file_name;

	k = ft_itoa(i);
	l = ft_itoa(j);
	file_name = ft_strjoin("", ".data_heredoc_");
	file_name = ft_strjoin(file_name, k);
	file_name = ft_strjoin(file_name, "_");
	file_name = ft_strjoin(file_name, l);
	return (file_name);
}

static bool	init_heredoc(t_redir *redir, int i, int j)
{
	t_heredoc	*h;

	h = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!h)
		return (false);
	h->file_name = heredoc_file_name(i, j);
	h->fd = open(h->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (h->fd == -1)
		return (free_heredoc(h, false));
	redir = redir->next_sibling;
	while (1)
	{
		h->input = readline("> ");
		if (!ft_strcmp(h->input, redir->txt))
			break ;
		h->reader = write(h->fd, h->input, ft_strlen(h->input));
		if (h->reader == -1)
			return (free_heredoc(h, false));
		h->reader = write(h->fd, "\n", 1);
		if (h->reader == -1)
			return (free_heredoc(h, false));
		free(h->input);
	}
	return (free_heredoc(h, true));
}

bool	define_heredocs(t_final *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds)
	{
		j = 0;
		if (cmds->redir)
		{
			while (cmds->redir)
			{
				if (cmds->redir->heredoc == 1)
					if (!init_heredoc(cmds->redir, i, j))
						return (false);
				j++;
				cmds->redir = cmds->redir->next_sibling;
			}
		}
		i++;
		cmds = cmds->next_sibling;
	}
	return (true);
}
