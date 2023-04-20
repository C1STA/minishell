/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:25:16 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 13:32:32 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

int	env_var_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

bool	init_values(t_heredoc *h, bool n)
{
	h->i = 0;
	if (!n)
		h->len = 0;
	h->tmp = NULL;
	h->k = 0;
	h->dollar = false;
	if (n)
	{
		h->dest = (char *)malloc(sizeof(char) * h->len + 1);
		if (!h->dest)
			return (print_perror("malloc"), false);
	}
	return (true);
}

void	heredoc_exit(t_final *cmds, char *env[], bool n)
{
	free_exe(&cmds, &env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (n)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
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
			redir = redir->next;
		}
		i++;
		cmds = cmds->next;
	}
}
