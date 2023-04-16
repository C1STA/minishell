/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:45:12 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 17:31:16 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*env_not_exist(void)
{
	t_env	*mini_env;

	mini_env = malloc(sizeof(t_env));
	mini_env -> next = NULL;
	mini_env -> txt = ft_strcpy("nothing=nothing");
	mini_env -> var_name = ft_strcpy("nothing");
	mini_env -> var_value = ft_strcpy("nothing");
	return (mini_env);
}

void	create_var_name_and_value(t_env *ptr)
{
	while (ptr != NULL)
	{
		create_var_name(ptr);
		create_var_value(ptr);
		ptr = ptr -> next;
	}
}

void	copy_original_to_mini(char *original[], int i, t_env *ptr)
{
	while (original[i] && ptr != NULL)
	{
		ptr -> txt = ft_strcpy(original[i]);
		ptr = ptr -> next;
		i++;
	}
}

int	env_checks_quit(t_env **head, t_node *node)
{
	if (!head)
		return (1);
	if ((!node))
		return (1);
	if ((node -> next == NULL) || ft_stcmp(node -> next -> txt, "|") == 1)
		return (1);
	return (0);
}

void	free_in_insert_input_env(char *env, char *var_name, char *var_value)
{
	free(env);
	free(var_name);
	free(var_value);
}
