/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:42 by dpinto            #+#    #+#             */
/*   Updated: 2025/01/26 16:49:18 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_name(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	ptr = malloc((sizeof(char) * i) + 1);
	i = 0;
	while (str[i] && str[i] != '=')
		ptr[j++] = str[i++];
	return (ptr[j] = '\0', ptr);
}

bool	is_there_equal(char *s)
{
	if (!s)
		return (false);
	while (*s)
	{
		if (*s == '=')
			return (true);
		s++;
	}
	return (false);
}

char	*extract_value(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str)
		return (NULL);
	if (!is_there_equal(str))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (!str[++i])
		return (NULL);
	ptr = ft_strdup(str + i);
	return (ptr);
}

static void	del_env(t_env **head, char *var_name, t_main *m)
{
	if (!ft_strcmp(var_name, "PWD"))
	{
		if (!m->pwd)
			m->pwd = getpwd(*head);
	}
	supp_env(head, var_name);
}

int	insert_input_env(t_env **head, t_node *node, t_main *m)
{
	char	*var_name;
	char	*var_value;
	char	*env_input;
	t_env	*last_node;

	if (env_checks_quit(head, node))
		return (1);
	node = node->next;
	while (node)
	{
		env_input = ft_strcpy_env(node->txt);
		var_name = extract_name(env_input);
		var_value = extract_value(env_input);
		if (!pars_env_name(var_name, env_input) && is_there_equal(env_input))
		{
			if (check_if_exist(*head, var_name) == 1)
				del_env(head, var_name, m);
			add_node_env(*head);
			last_node = last_env_node(*head);
			fill_last_node(last_node, var_name, var_value, env_input);
		}
		free_in_insert_input_env(env_input, var_name, var_value);
		node = node->next;
	}
	return (0);
}
