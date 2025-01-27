/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:42:34 by wacista           #+#    #+#             */
/*   Updated: 2025/01/26 16:49:23 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_env_node(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	if (!ptr)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static char	*get_child(t_node *child)
{
	char	*dest;

	while (child)
	{
		if (child->txt)
			dest = child->txt;
		child = child->next;
	}
	return (dest);
}

int	update_cmd(t_env **mini_env, t_node *child)
{
	t_env	**head;
	t_env	*ptr;
	t_env	*last_node;
	char	*full;
	char	*txt;

	head = mini_env;
	ptr = *mini_env;
	txt = get_child(child);
	full = ft_strjoin("_=", txt);
	while (ptr)
	{
		if (!ft_strncmp(ptr->txt, "_", 1) && ptr->txt[1] == '=')
		{
			if (check_if_exist(*head, ptr->var_name) == 1)
				supp_env(head, ptr->var_name);
			add_node_env(*head);
			last_node = last_env_node(*head);
			return (fill_last_node(last_node, "_", txt, full), free(full), 0);
		}
		ptr = ptr->next;
	}
	add_node_env(*head);
	last_node = last_env_node(*head);
	return (fill_last_node(last_node, "_", txt, full), free(full), 0);
}
