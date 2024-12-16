/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:38:06 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:38:07 by wacista          ###   ########.fr       */
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
