/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:35:42 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 02:32:26 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

void	free_all(t_final *cmds)
{
	t_final	*tmp;

	while (cmds)
	{
		tmp = cmds->next_sibling;
		free(cmds->redir);
		free(cmds);
		cmds = tmp;
	}
}

/* static void	attributes(t_final *node, int i)
{
		node->cmds = NULL;
		node->redir->txt = NULL;
		node->redir->heredoc = i;
		node->redir->in_file = i;
		node->redir->out_file = i;
		node->redir->append = i;
		node->redir->file = i;
} */

/* t_final	*init_all(char *txt)
{
	t_final	*head;
	t_final	*tail;
	t_final	*node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (i < 10)
	{
		node = (t_final *)malloc(sizeof(t_final));
		node->next_sibling = NULL;
		node->redir = (t_redir *)malloc(sizeof(t_redir));
		attributes(node, i);
		if (!head)
			head = node;
		if (tail)
			tail->next_sibling = node;
		tail = node;
		i++;
	}
	return (head);
} */

int	lenlist(t_final *L)
{
	int	len;

	len = 0;
	while (L)
	{
		len++;
		L = L->next_sibling;
	}
	return (len);
}

void	print_struct(t_final *cmds)
{
	while (cmds)
	{
		printf("file = %d\n", cmds->redir->file);
		cmds = cmds->next_sibling;
	}
}

static t_final	*createcell(int data)
{
	t_final	*cell;

	cell = malloc(sizeof(t_final));
	if (!cell)
		return (NULL);
	cell->redir->append = data;
	cell->next_sibling = NULL;
	return (cell);
}

t_final	*addat(t_final *L, int data, int pos)
{
	t_final	*precedent;
	t_final	*current;
	t_final	*cell;
	int		i;

	precedent = L;
	current = L;
	cell = createcell(data);
	if (!(L))
		return (cell);
	if (pos == 0)
	{
		cell->next_sibling = L;
		return (cell);
	}
	i = 0;
	while (i < pos)
	{
		i++;
		precedent = current;
		current = current->next_sibling;
	}
	precedent->next_sibling = cell;
	cell->next_sibling = current;
	return (L);
}
