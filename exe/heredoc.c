/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 19:16:50 by wcista            #+#    #+#             */
/*   Updated: 2023/04/21 02:20:30 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

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

char	*heredoc_file_name(int i, int j)
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

static bool	init_heredoc(char *env[], t_redir *redir, int i, int j)
{
	t_heredoc	*h;

	h = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!h)
		return (false);
	h->file_name = heredoc_file_name(i, j);
	h->fd = open(h->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (h->fd == -1)
		return (free_heredoc(h, false));
	redir = redir->next;
	while (1)
	{
		h->input = readline("> ");
		if (!ft_strcmp(h->input, redir->txt))
			break ;
		h->input = heredoc_expand(h, env, false);
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

static void	define_heredoc(t_final *cmds, char *env[])
{
	int		i;
	int		j;
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;

	i = 0;
	tmp_cmds = cmds;
	while (tmp_cmds)
	{
		j = 0;
		tmp_redir = tmp_cmds->redir;
		while (tmp_redir)
		{
			if (tmp_redir->heredoc == 1)
			{
				if (!init_heredoc(env, tmp_redir, i, j))
					return (heredoc_exit(cmds, env, false));
			}
			tmp_redir = tmp_redir->next;
			j++;
		}
		i++;
		tmp_cmds = tmp_cmds->next;
	}
	return (heredoc_exit(cmds, env, true));
}

bool	ft_heredoc(t_final *cmds, char *env[])
{
	pid_t	pid;

	if (!is_heredoc(cmds))
		return (true);
	pid = fork();
	if (pid == -1)
		return (print_perror("fork"), false);
	if (pid == 0)
		define_heredoc(cmds, env);
	waitpid(pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
	{
		g_exit_status = (WEXITSTATUS(g_exit_status));
		if (g_exit_status != 0)
			return (false);
	}
	return (true);
}
