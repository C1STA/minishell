/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:40:30 by wcista            #+#    #+#             */
/*   Updated: 2023/04/24 20:45:28 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt(t_prompt *p)
{
	if (p->user)
		free(p->user);
	if (p->name)
		free(p->name);
	if (p->pwd)
		free(p->pwd);
	free(p);
}

void	init_to_null(t_prompt *p)
{
	p->len = 0;
	p->i = 0;
	p->j = 0;
	p->status = 0;
	p->name = NULL;
	p->user = NULL;
	p->pwd = NULL;
}
