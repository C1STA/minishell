/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:09 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:10 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_last_node(t_env *last_node, char *name, char *value, char *env)
{
	last_node->var_name = ft_strdup(name);
	if (value)
		last_node->var_value = ft_strdup(value);
	else
		last_node->var_value = ft_strdup("");
	last_node->txt = ft_strdup(env);
}

char	*return_after(char *str, int j, int save)
{
	int		i;
	int		length;
	char	*after;

	length = 0;
	i = 0;
	while (str[j])
	{
		j++;
		length++;
	}
	after = malloc(sizeof(char) * (length + 1));
	while (str[save] != '\0')
	{
		after[i] = str[save];
		i++;
		save++;
	}
	after[i] = '\0';
	return (after);
}

void	final_txt(char *a_dol, char *new_str, t_node *ptr, char *save_var)
{
	char	*tmp;

	if (a_dol)
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, a_dol);
		free(tmp);
	}
	free(ptr->txt);
	free(save_var);
	free(a_dol);
	ptr->txt = new_str;
}

char	*init_save_after_dollar(char *save_after_dollar)
{
	save_after_dollar = malloc(sizeof(char) * 2);
	save_after_dollar[0] = 'a';
	save_after_dollar[1] = '\0';
	return (save_after_dollar);
}

char	*return_after_multiple_dollar(char *str, int i, int save)
{
	int		count;
	char	*after;

	while (str[i] != '\0')
		i++;
	count = i - save;
	after = malloc(sizeof(char) * (count + 1));
	i = 0;
	while (str[save] != '\0')
	{
		after[i] = str[save];
		i++;
		save++;
	}
	after[i] = '\0';
	return (after);
}
