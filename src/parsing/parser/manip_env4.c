/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:47 by dpinto            #+#    #+#             */
/*   Updated: 2025/01/13 20:59:23 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*return_matching_value(t_env *head, char *str)
{
	t_env	*ptr;
	char	*exit;

	ptr = head;
	if (!ptr || !str)
		return (NULL);
	exit = ft_itoa(g_exit_status);
	if (ft_stcmp(str, exit))
		return (free(exit), str);
	free(exit);
	while (ptr != NULL)
	{
		if (ft_stcmp(str, ptr->txt) == 1 && ptr->txt[ft_strlen(str)] == '=')
			return (ptr->var_value);
		ptr = ptr->next;
	}
	return (NULL);
}

void	cut_dollar_sign(char *str)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(str);
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	length = length - 1;
	str[length] = '\0';
}

char	*catch_var(char *str)
{
	int		i;
	int		length;
	char	*var;

	if (!str)
		return (NULL);
	if (*str == '?')
	{
		var = ft_itoa(g_exit_status);
		return (var);
	}
	length = 0;
	i = 0;
	while (expand_legtimate_values(str[length]))
		length++;
	var = malloc(sizeof(char) * (length + 1));
	while (expand_legtimate_values(str[i]))
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*before_dollar(char *str)
{
	int		i;
	int		length;
	char	*before;

	i = 0;
	length = 0;
	while (str[length] != '$')
		length++;
	before = malloc(sizeof(char) * (length + 1));
	while (str[i] != '$')
	{
		before[i] = str[i];
		i++;
	}
	before[i] = '\0';
	return (before);
}

char	*after_dollar(char *str)
{
	int	j;
	int	save;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '$')
			break ;
		j++;
	}
	if (str[j] == '\0')
		return (NULL);
	j++;
	while (str[j] != '\0')
	{
		if (str[j] == '$')
			break ;
		j++;
	}
	if (str[j] == '\0')
		return (NULL);
	save = j;
	return (return_after(str, j, save));
}
