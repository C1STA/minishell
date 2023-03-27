#include "../../minishell.h"

static char	*heredoc_file_name(int i, int j)
{
	char	*k;
	char	*l;
	char	*file_name;

	k = ft_itoa(i);
	l = ft_itoa(j);
	file_name = ft_strjoin("", ".data_heredoc_");
	file_name = ft_strjoin(file_name, k);
	printf("%s, %s\n", k, l);
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
	printf("\n%s\n", h->file_name);
	h->fd = open(h->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (h->fd == -1)
	{
		free(h->file_name);
		free(h);
		return (false);
	}
	redir = redir->next_sibling;
	while (1)
	{
		h->input = readline("> ");
		if (!ft_strcmp(h->input, redir->txt))
			break ;
		h->reader = write(h->fd, h->input, ft_strlen(h->input));
		if (h->reader == -1)
		{
			free(h->file_name);
			free(h->input);
			close(h->fd);
			free(h);
			return (false);
		}
		h->reader = write(h->fd, "\n", 1);
		if (h->reader == -1)
		{
			free(h->file_name);
			free(h->input);
			close(h->fd);
			free(h);
			return (false);
		}
		free(h->input);
	}
	close (h->fd);
	printf("REDIR:::%s:::\n", redir->txt);
	free(h->file_name);
	free(h->input);
	free(h);
	return (true);
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
