/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:29:02 by wcista            #+#    #+#             */
/*   Updated: 2023/04/18 00:28:45 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exe.h"

static void	free_prompt(t_prompt *p)
{
	free(p->user);
	free(p->name);
	free(p->pwd);
	free(p);
}

static void	get_len_and_names(t_env *env, t_prompt *p)
{
	t_env		*env_tmp;

	env_tmp = env;
	p->len = 0;
	p->i = 0;
	p->j = 0;
	while (env_tmp)
	{
		if (!ft_strcmp(env_tmp->var_name, "USER"))
		{
			p->len += ft_strlen(env_tmp->var_value);
			p->user = ft_strcpy(env_tmp->var_value);
		}
		else if (!ft_strcmp(env_tmp->var_name, "NAME"))
		{
			p->len += ft_strlen(env_tmp->var_value);
			p->name = ft_strcpy(env_tmp->var_value);
		}
		else if (!ft_strcmp(env_tmp->var_name, "PWD"))
		{
			p->len += ft_strlen(env_tmp->var_value);
			p->pwd = ft_strcpy(env_tmp->var_value);
		}
		env_tmp = env_tmp->next;
	}
}

char	*get_prompt_name(t_env *env)
{
	t_prompt	*p;
	char		*dest;

	p = (t_prompt *)malloc(sizeof(t_prompt));
	if (!p)
		return (NULL);
	get_len_and_names(env, p);
	dest = (char *)malloc(sizeof(char) * (p->len + 5));
	if (!dest)
		return (NULL);
	while (p->i < ft_strlen(p->user))
		dest[p->i++] = p->user[p->j++];
	dest[p->i++] = '@';
	p->j = 0;
	while (p->j < ft_strlen(p->name))
		dest[p->i++] = p->name[p->j++];
	dest[p->i++] = ':';
	p->j = 0;
	while (p->j < ft_strlen(p->pwd))
		dest[p->i++] = p->pwd[p->j++];
	dest[p->i++] = '$';
	dest[p->i++] = ' ';
	dest[p->i++] = '\0';
	free_prompt(p);
	return (dest);
}
