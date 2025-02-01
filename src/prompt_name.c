/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:38:15 by wacista           #+#    #+#             */
/*   Updated: 2025/01/31 16:38:38 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exe.h"

static char	*default_name(void)
{
	char	*name;

	name = ft_strdup("minishell$ ");
	return (name);
}

/* static void	get_cluster_position(t_env *env, t_prompt *p, bool n)
{
	p->i_gcp = 0;
	if (!n)
		p->save_len = p->len;
	else
		p->name = (char *)malloc(sizeof(char) * p->save_len + 1);
	while (env->var_value[p->i_gcp] && env->var_value[p->i_gcp] != '/')
		p->i_gcp++;
	p->i_gcp++;
	p->j_gcp = 0;
	while (env->var_value[p->i_gcp] && env->var_value[p->i_gcp] != '.')
	{
		if (!n)
		{
			p->len++;
			p->i_gcp++;
		}
		else
			p->name[p->j_gcp++] = env->var_value[p->i_gcp++];
	}
	if (n)
		p->name[p->j_gcp] = '\0';
	else
		return (p->save_len = p->len - p->save_len, \
		get_cluster_position(env, p, true));
} */

static char	*get_pwd_format(t_env *env, t_prompt *p, char	*pwd)
{
	char	*home;

	home = get_env(env, "HOME");
	if (!home)
		return (p->len += ft_strlen(pwd), p->pwd = ft_strdup(pwd));
	if (!ft_strncmp(pwd, home, ft_strlen(home)) && \
	((pwd[ft_strlen(home)] == '/') || (pwd[ft_strlen(home)]) == '\0'))
	{
		p->pwd = ft_strjoin("~", pwd + ft_strlen(home));
		if (!p->pwd)
			return (p->len += ft_strlen(pwd), p->pwd = ft_strdup(pwd));
		return (p->len += ft_strlen(p->pwd), p->pwd);
	}
	return (p->len += ft_strlen(pwd), p->pwd = ft_strdup(pwd));
}

static void	len_and_names_loop(t_env *env_tmp, t_prompt *p)
{
	t_env	*head;

	head = env_tmp;
	while (env_tmp)
	{
		if (!ft_strcmp(env_tmp->var_name, "USER"))
		{
			p->status++;
			p->len += ft_strlen(env_tmp->var_value);
			p->user = ft_strdup(env_tmp->var_value);
		}
		else if (!ft_strcmp(env_tmp->var_name, "NAME"))
		{
			p->status++;
			p->len += ft_strlen(env_tmp->var_value);
			p->name = ft_strdup(env_tmp->var_value);
			//get_cluster_position(env_tmp, p, false);
		}
		else if (!ft_strcmp(env_tmp->var_name, "PWD"))
		{
			p->status++;
			get_pwd_format(head, p, env_tmp->var_value);
		}
		env_tmp = env_tmp->next;
	}
}

static bool	get_len_and_names(t_env *env, t_prompt *p, t_main *m)
{
	t_env		*env_tmp;

	env_tmp = env;
	init_to_null(p);
	len_and_names_loop(env_tmp, p);
	if (p->status == 2 && !p->pwd)
	{
		p->status++;
		get_pwd_format(env, p, m->pwd);
	}
	if (p->status != 3)
		return (free_prompt(p), false);
	return (true);
}

char	*get_prompt_name(t_env *env, t_main *m)
{
	t_prompt	*p;
	char		*dest;

	p = (t_prompt *)malloc(sizeof(t_prompt));
	if (!get_len_and_names(env, p, m))
		return (default_name());
	dest = (char *)malloc(sizeof(char) * (p->len + 5));
	if (!dest)
		return (free_prompt(p), default_name());
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
	return (free_prompt(p), dest);
}
