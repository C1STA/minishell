/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:38:06 by wacista           #+#    #+#             */
/*   Updated: 2025/01/27 05:58:59 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env	*env, char *var)
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, var))
			return (env->var_value);
		env = env->next;
	}
	return (NULL);
}

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

static int	ft_is_print(int c)
{
	if (c == '\t')
		return (1);
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

bool	is_printable(char *s)
{
	if (!s)
		return (false);
	while (*s)
	{
		if (ft_is_print(*s++))
			return (true);
	}
	return (false);
}
