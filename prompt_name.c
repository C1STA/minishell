/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:29:02 by wcista            #+#    #+#             */
/*   Updated: 2023/04/23 17:12:05 by wcista           ###   ########.fr       */
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

static void	get_cluster_position(t_env *env, t_prompt *p)
{
	int	i;
	int	j;

	i = 0;
	p->name = (char *)malloc(sizeof(char) * 7);
	while (env->var_value[i] && env->var_value[i] != '/')
		i++;
	i++;
	j = 0;
	while (env->var_value[i] && env->var_value[i] != '.')
	{
		p->len++;
		p->name[j++] = env->var_value[i++];
	}
	p->name[j] = '\0';
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
		else if (!ft_strcmp(env_tmp->var_name, "SESSION_MANAGER"))
			get_cluster_position(env_tmp, p);
		else if (!ft_strcmp(env_tmp->var_name, "PWD"))
		{
			p->len += ft_strlen(env_tmp->var_value);
			p->pwd = ft_strcpy(env_tmp->var_value);
		}
		env_tmp = env_tmp->next;
	}
}

char	*default_name(void)
{
	char	*name;

	name = ft_strcpy("minishell> ");
	return (name);
}

char	*get_prompt_name(t_env *env)
{
	t_prompt	*p;
	char		*dest;

	if (!ft_strcmp(env->var_name, "nothing"))
		return (default_name());
	p = (t_prompt *)malloc(sizeof(t_prompt));
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
