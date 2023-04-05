/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:16:50 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 20:06:45 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

static bool	free_heredoc(t_heredoc *h, t_final *cmds, bool n)
{
	if (h->fd)
		close(h->fd);
	if (h->file_name)
		free(h->file_name);
	if (h->input)
		free(h->input);
	if (h)
		free(h);
	ft_free_final_ast(&cmds);
	return (n);
}

static char	*heredoc_file_name(int i, int j)
{
	char	*k;
	char	*l;
	char	*file_name;

	k = ft_itoa(i);
	l = ft_itoa(j / 2);
	file_name = ft_strjoin_free("", ".data_heredoc_");
	file_name = ft_strjoin_free(file_name, k);
	file_name = ft_strjoin_free(file_name, "_");
	file_name = ft_strjoin_free(file_name, l);
	free(k);
	free(l);
	return (file_name);
}

static bool	init_heredoc(t_final *cmds, int i, int j)
{
	t_heredoc	*h;

	h = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!h)
		return (false);
	h->file_name = heredoc_file_name(i, j);
	h->fd = open(h->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (h->fd == -1)
		return (free_heredoc(h, cmds, false));
	cmds->redir = cmds->redir->next_sibling;
	while (1)
	{
		h->input = readline("> ");
		if (!ft_strcmp(h->input, cmds->redir->txt))
			break ;
		h->reader = write(h->fd, h->input, ft_strlen(h->input));
		if (h->reader == -1)
			return (free_heredoc(h, cmds, false));
		h->reader = write(h->fd, "\n", 1);
		if (h->reader == -1)
			return (free_heredoc(h, cmds, false));
		free(h->input);
	}
	return (free_heredoc(h, cmds, true));
}

static void	define_heredoc(t_final *cmds)
{
	int		i;
	int		j;

	printf("LE PID DU PROCESSUS HEREDOC EST : __________________%d\n", getpid());
	i = 0;
	while (cmds)
	{
		j = 0;
		while (cmds->redir)
		{
			if (cmds->redir->heredoc == 1)
				if (!init_heredoc(cmds, i, j))
					exit(EXIT_FAILURE);
			j++;
			cmds->redir = cmds->redir->next_sibling;
		}
		i++;
		cmds = cmds->next_sibling;
	}
	exit(EXIT_SUCCESS);
}

void	remove_heredoc(t_final *cmds)
{
	int		i;
	int		j;
	char	*file_name;
	t_redir	*redir;

	i = 0;
	while (cmds)
	{
		j = 0;
		redir = cmds->redir;
		while (redir)
		{
			if (redir->heredoc == 1)
			{
				file_name = heredoc_file_name(i, j);
				unlink(file_name);
				free(file_name);
			}
			j++;
			redir = redir->next_sibling;
		}
		i++;
		cmds = cmds->next_sibling;
	}
}

bool	ft_heredoc(t_final *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork error"), false);
	if (pid == 0)
		define_heredoc(cmds);
	wait(&g_exit_status);
	if (WIFEXITED(g_exit_status))
	{
		g_exit_status = (WEXITSTATUS(g_exit_status));
		if (g_exit_status != 0)
			return (false);
	}
	return (true);
}

