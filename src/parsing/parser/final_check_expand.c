/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:48:42 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/07 19:27:24 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_tab(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	free(str);
}

int	nbr_space(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' )
			count++;
		i++;
	}
	return (count);
}

char	*return_right_tab(char *str, int begin, int end)
{
	char	*tab;

	if (begin > end)
		tab = return_right_tab_begin_sup(str, begin, end);
	else if (begin < end)
		tab = return_right_tab_begin_inf(str, begin, end);
	else
		return (NULL);
	return (tab);
}

char	*return_right_tab_begin_sup(char *str, int begin, int end)
{
	char	*tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char) * (((begin - 1) - end) + 1));
	while (begin > end)
	{
		if (str[end])
			tab[i] = str[end];
		i++;
		end++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*return_right_tab_begin_inf(char *str, int begin, int end)
{
	char	*tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char) * ((end - begin) + 1));
	while (end > begin)
	{
		if (str[begin])
			tab[i] = str[begin];
		i++;
		begin++;
	}
	tab[i] = '\0';
	return (tab);
}
