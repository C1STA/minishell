/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:03 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:04 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_not_exist(void)
{
	t_env	*mini_env;
	t_env	*start;

	mini_env = (t_env *)malloc(sizeof(t_env) * 4);
	start = mini_env;
	mini_env->txt = ft_strdup("nothing=nothing");
	mini_env->var_name = ft_strdup("nothing");
	mini_env->var_value = ft_strdup("nothing");
	add_node_env(mini_env);
	add_node_env(mini_env);
	mini_env = mini_env->next;
	mini_env->txt = ft_strdup("OLDPWD=null");
	mini_env->var_name = ft_strdup("OLDPWD");
	mini_env->var_value = ft_strdup("null");
	mini_env = mini_env->next;
	mini_env->var_value = getcwd(NULL, 0);
	if (!mini_env->var_value)
		mini_env->var_value = ft_strdup("null");
	mini_env->txt = ft_strjoin("PWD=", mini_env->var_value);
	mini_env->var_name = ft_strdup("PWD");
	mini_env->next = NULL;
	mini_env = start;
	return (mini_env);
}

void	create_var_name_and_value(t_env *ptr)
{
	while (ptr != NULL)
	{
		create_var_name(ptr);
		create_var_value(ptr);
		ptr = ptr->next;
	}
}

void	copy_original_to_mini(char *original[], int i, t_env *ptr)
{
	while (original[i] && ptr != NULL)
	{
		ptr->txt = ft_strdup(original[i]);
		ptr = ptr->next;
		i++;
	}
}

int	check_if_one_cmd(t_node *node)
{
	while (node)
	{
		if (ft_stcmp(node->txt, "|"))
			return (1);
		node = node->next;
	}
	return (0);
}

int	env_checks_quit(t_env **head, t_node *node)
{
	if (!head)
		return (1);
	if ((!node))
		return (1);
	if ((node->next == NULL) || check_if_one_cmd(node))
		return (1);
	return (0);
}
