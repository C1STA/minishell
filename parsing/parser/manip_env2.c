/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:34:13 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 15:58:31 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_var_name(t_env *node)
{
	int	i;

	if (!node)
		return ;
	if (node -> txt == NULL)
		return ;
	i = 0;
	while (node -> txt[i] != '=')
		i++;
	node -> var_name = malloc((sizeof(char)) * i + 1);
	if (node -> var_name == NULL)
		return ;
	i = 0;
	while (node -> txt[i] != '=')
	{
		node -> var_name[i] = node -> txt[i];
		i++;
	}
	node ->var_name[i] = '\0';
}

t_env	*copy_env(char *original[])
{
	int		i;
	t_env	*mini_env;
	t_env	*ptr;

	i = 0;
	if (!original || original[0] == NULL)
		return (env_not_exist());
	mini_env = malloc(sizeof(t_env));
	if (mini_env == NULL)
		return (NULL);
	mini_env -> next = NULL;
	while (original[i])
		i++;
	while (i > 1)
	{
		mini_env = add_node_env(mini_env);
		i--;
	}
	i--;
	ptr = mini_env;
	copy_original_to_mini(original, i, ptr);
	ptr = mini_env;
	create_var_name_and_value(ptr);
	return (mini_env);
}

void	print_env(t_env *head)
{
	t_env	*ptr;

	if (!head)
		return ;
	ptr = head;
	while (ptr != NULL)
	{
		ft_printf("%s\n", ptr -> txt);
		ptr = ptr -> next;
	}
}

int	ft_stcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (0);
	if (!str2)
		return (0);
	if (str1[0] == '\0')
		return (0);
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_nbr(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
