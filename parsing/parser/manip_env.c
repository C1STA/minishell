/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:47:11 by imrane            #+#    #+#             */
/*   Updated: 2023/04/22 20:56:29 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strcpy(char *str)
{
	int		i;
	int		length;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	length = ft_strlen(str);
	ptr = malloc((sizeof(char) * length) + 1);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
char	*ft_strcpy_env(char *str)
{
	int		i;
	int		length;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	length = ft_strlen(str);
	ptr = malloc(sizeof(char) *(length + 1));
	if (!ptr)
		return (NULL);
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
	{
		// en gros c que qudn ya des guillemets que jqccepte les espace
		// jenleve les guillemets
		//en fait la logique denregistrement cest celle du jeneleve les guillemets
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);

}*/

char	*ft_strcpy_env(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) *(ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		if_double_env(ptr, &i, &j, str);
		if (!str[i])
			break ;
		if_simple_env(ptr, &i, &j, str);
		if (!str[i])
			break ;
		if (str[i] != '\'' && str[i] != '"')
		{
			ptr[j] = str[i];
			j++;
		}
		i++;
	}
	return (ptr[j] = '\0', ptr);
}

t_env	*new_node_env(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node -> next = NULL;
	node -> txt = NULL;
	node -> var_name = NULL;
	node -> var_value = NULL;
	return (node);
}

t_env	*add_node_env(t_env *head)
{
	t_env	*ptr;

	if (!head)
		return (NULL);
	ptr = head;
	if (head -> next == NULL)
	{
		head -> next = new_node_env();
		return (head);
	}
	else
	{
		while (ptr -> next != NULL)
			ptr = ptr -> next;
		ptr -> next = new_node_env();
	}
	return (head);
}
