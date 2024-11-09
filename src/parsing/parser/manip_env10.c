/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:01:08 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/07 19:27:24 by wacista          ###   ########.fr       */
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

char	*find_end_of_var(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '$' && str[i] != ' ' \
		&& str[i] != '\t' && str[i] != '\'' && str[i] != '"')
		i++;
	if (str)
		str = str + i;
	return (str);
}

char	*after_dollar_deux(char *str)
{
	int		i;
	char	*after;
	int		length;

	if (!str)
		return (NULL);
	length = 0;
	i = 0;
	while (str[length] != '\0')
		length++;
	after = malloc(sizeof(char) * (length + 1));
	while (str[i] != '\0')
	{
		after[i] = str[i];
		i++;
	}
	after[i] = '\0';
	return (after);
}
