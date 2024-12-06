/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:01:08 by imoumini          #+#    #+#             */
/*   Updated: 2024/12/06 13:14:19 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nbr_env(t_env *node)
{
	t_env	*ptr;
	int		i;

	i = 0;
	if (!node)
		return (0);
	ptr = node;
	while (ptr)
	{
		i++;
		ptr = ptr -> next;
	}
	return (i);
}

char	**transform_env_in_double_tab(t_env *node)
{
	int		i;
	char	**new_str;
	t_env	*ptr;

	if (!node)
		return (NULL);
	ptr = node;
	i = 0;
	new_str = malloc(sizeof(char *) * (count_nbr_env(node) +1));
	new_str[count_nbr_env(node)] = NULL;
	while (ptr)
	{
		new_str[i] = ft_strcpy(ptr -> txt);
		i++;
		ptr = ptr -> next;
	}
	return (new_str);
}

void	print_double_tab_env(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

int	expand_legtimate_values(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*find_end_of_var(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	if (*str == '?')
		return (str + 1);
	else if (ft_isdigit(*str))
		return (str + 1);
	i = 0;
	while (expand_legtimate_values(str[i]))
		i++;
	if (str)
		str = str + i;
	return (str);
}
