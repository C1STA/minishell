/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_option.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:29:48 by wacista           #+#    #+#             */
/*   Updated: 2025/01/19 06:29:19 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*getpwd(t_env *head)
{
	char	*dest;
	t_env	*ptr;

	if (!head)
		return (NULL);
	ptr = head;
	while (ptr)
	{
		if (!ft_strcmp(ptr->var_name, "PWD"))
		{
			dest = ft_strdup(ptr->var_value);
			return (dest);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

int	is_empty(t_node *root, int empty)
{
	int		len;
	t_node	*ptr;

	len = 0;
	if (!root)
		return (true);
	ptr = root;
	while (root)
	{
		root = root->next;
		len++;
	}
	while (ptr)
	{
		if (!ptr->txt)
			empty++;
		ptr = ptr->next;
	}
	if (len == empty)
		return (true);
	return (false);
}

int	is_env_var(t_env *mini_env, t_node *root, t_main *m)
{
	t_node	*ptr;

	if (!root)
		return (1);
	ptr = root->first_child;
	if (ptr)
	{
		if (!ft_strcmp(ptr->txt, "export") && ptr->next && !is_empty(ptr, 1))
		{
			if (insert_input_env(&mini_env, ptr, m) == 0)
			{
				update_cmd(&mini_env, ptr);
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

int	pars_env_name(char *str, char *env_input)
{
	if (!str || !env_input)
		return (1);
	if (!ft_isalpha(*str))
		return (print_error_export(env_input), 1);
	while (*str)
	{
		if (!ft_isalnum(*str))
			return (print_error_export(env_input), 1);
		str++;
	}
	return (0);
}
