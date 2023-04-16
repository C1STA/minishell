/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:34:36 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 16:06:36 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_name(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	ptr = malloc((sizeof(char) * i) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*extract_value(char *str)
{
	int		i;
	int		equal;
	char	*ptr;

	i = 0;
	equal = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	equal = i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		i++;
	ptr = malloc((sizeof(char)) *(i - equal) + 1);
	equal++;
	i = 0;
	while (str[equal] != '\0' && str[equal] != ' ' && str[equal] != '\t')
	{
		ptr[i] = str[equal];
		i++;
		equal++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_env	*last_env_node(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	if (!ptr)
		return (NULL);
	while (ptr -> next != NULL)
		ptr = ptr -> next;
	return (ptr);
}

int	insert_input_env(t_env **head, t_node *node, int pipe)
{
	char	*var_name;
	char	*var_value;
	char	*env_input;
	t_env	*last_node;

	if (env_checks_quit(head, node) == 1)
		return (1);
	env_input = ft_strcpy_env(node -> next -> txt);
	var_name = extract_name(node -> next -> txt);
	var_value = extract_value(node -> next -> txt);
	if (pars_env_name(var_name, env_input) == 0 && (pipe == 0) \
		&& (pars_env_value(var_value, env_input) == 0) \
		&& count_nbr_equal(env_input, env_input) == 0)
	{
		if (check_if_exist(*head, var_name) == 1)
			supp_env(head, var_name);
		add_node_env(*head);
		last_node = last_env_node(*head);
		return (fill_last_node(last_node, var_name, var_value, env_input), 1);
	}
	else
	{
		free_in_insert_input_env(env_input, var_name, var_value);
		return (0);
	}
}

t_node	*do_i_have_to_expand(t_node *node)
{
	t_node	*ptr;
	int		i;

	i = 0;
	if (!node)
		return (NULL);
	ptr = node;
	if (node -> after_here_doc == 1)
		return (NULL);
	if (ptr != NULL)
	{
		while (ptr -> txt[i] != '\0')
		{
			if (ptr -> txt[i] == '$')
				return (ptr);
			i++;
		}
	}
	return (NULL);
}
