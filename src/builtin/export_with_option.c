/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_option.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:29:48 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:29:49 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	is_env_var(t_env *mini_env, t_node *root)
{
	t_node	*ptr;

	if (!root)
		return (1);
	ptr = root -> first_child;
	if (ptr)
	{
		if (ft_stcmp(ptr -> txt, "export") && (ptr -> next != NULL))
		{
			if (insert_input_env(&mini_env, ptr) == 0)
				return (0);
		}
		ptr = ptr -> next;
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
