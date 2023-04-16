/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:35:48 by imrane            #+#    #+#             */
/*   Updated: 2023/04/14 16:48:32 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	next_char(t_source *src)
{
	char	nc;

	nc = '\n';
	if (!src || !src->buffer)
	{
		return (nc);
	}
	if (src -> buffer[src -> curpos])
	{
		nc = src -> buffer[src -> curpos + 1];
		src -> curpos++;
		return (nc);
	}
	return (nc);
}

void	unget_char(t_source *src)
{
	if (!src || !src->buffer)
		return ;
	if (src -> curpos == 0)
		return ;
	else
		src -> curpos--;
}

char	peek_char(t_source *src)
{
	char	nc;

	nc = '\n';
	if (!src || !src->buffer)
		return (nc);
	if (src -> buffer[src -> curpos])
	{
		nc = src -> buffer[src -> curpos + 1];
		return (nc);
	}
	return (nc);
}

void	skip_white_spaces(t_source *src)
{
	if (!src || !src->buffer)
		return ;
	while (src -> buffer[src -> curpos] \
		&& (src -> buffer[src -> curpos] == ' ' \
		|| src -> buffer[src -> curpos] == '\t'))
		src -> curpos++;
}
