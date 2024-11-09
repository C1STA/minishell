/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 10:18:14 by wcista            #+#    #+#             */
/*   Updated: 2024/11/07 19:26:04 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static char	**dup_env(char *env[])
{
	int		i;
	int		len;
	char	**env_copy;

	len = ft_tablen(env);
	env_copy = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env_copy)
		return (print_perror("malloc"), NULL);
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(env[i]);
		if (!env_copy[i])
			return (print_perror("malloc"), NULL);
		i++;
	}
	env_copy[len] = NULL;
	return (env_copy);
}

static void	sort_env(char *env[])
{
	t_export	*e;

	e = (t_export *)malloc(sizeof(t_export));
	if (!e)
		return (print_perror("malloc"));
	e->i = 0;
	e->len = (int)ft_tablen(env);
	while (e->i < e->len - 1)
	{
		e->min_idx = e->i;
		e->j = e->i + 1;
		while (e->j < e->len)
		{
			if (ft_strcmp_e(env[e->j], env[e->min_idx]) < 0)
				e->min_idx = e->j;
			e->j++;
		}
		if (e->min_idx != e->i)
			ft_swap(&env[e->i], &env[e->min_idx]);
		e->i++;
	}
	free(e);
}

static void	print_env_cpy(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(str[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

bool	builtin_export(char *env[], t_pipex *p)
{
	char	**env_tmp;

	env_tmp = dup_env(env);
	sort_env(env_tmp);
	print_env_cpy(env_tmp);
	free_final_env(&env_tmp);
	p->exit_status = 0;
	return (true);
}
